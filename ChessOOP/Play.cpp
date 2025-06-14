#include "Play.h"
#include "PieceFactory.h"

Game::Game() : currentPlayer(Colour::WHITE), gameState(GameState::PLAYING) {
    updateGameState();
    addToHistory();
}

GameState Game::getGameState() const { 
    return gameState; 
}

Colour Game::getCurrentPlayer() const { 
    return currentPlayer; 
}

bool Game::makeMove(const String& moveStr) {
    int fromRow, fromCol, toRow, toCol;
    if (parseAlgebraicNotation(moveStr, fromRow, fromCol, toRow, toCol) != "") {
        std::wcout << L"Invalid move format!" << std::endl;
        return false;
    }
    return makeMove(fromRow, fromCol, toRow, toCol);
}

bool Game::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (gameState != GameState::PLAYING && gameState != GameState::CHECK) {
        return false;
    }

    if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
        return false;
    }

    Piece* piece = board.get(fromRow, fromCol);
    if (!piece || piece->getColor() != currentPlayer) {
        return false;
    }

    // Create move record
    Move move(fromRow, fromCol, toRow, toCol);
    move.capturedPiece = board.get(toRow, toCol);

    // Check for special moves
    if (piece->getType() == Type::KING && std::abs(toCol - fromCol) == 2) {
        // Castling
        move.isCastling = true;
        if (!performCastling(currentPlayer, toCol > fromCol)) {
            return false;
        }
    }
    else if (piece->getType() == Type::PAWN && toCol != fromCol && !board.get(toRow, toCol)) {
        // En passant
        move.isEnPassant = true;
        int captureRow = (currentPlayer == Colour::WHITE) ? toRow + 1 : toRow - 1;
        move.capturedPiece = board.get(captureRow, toCol);
        board.set(captureRow, toCol, nullptr);
        board.set(toRow, toCol, piece, fromRow, fromCol);
    }
    else if (piece->getType() == Type::PAWN &&
        ((currentPlayer == Colour::WHITE && toRow == 0) ||
            (currentPlayer == Colour::BLACK && toRow == 7))) {
        // Pawn promotion
        move.isPromotion = true;
        move.promotionType = getPromotionChoice();

        board.set(fromRow, fromCol, nullptr);
        delete board.get(toRow, toCol); // Delete captured piece if any

        // Create promoted piece
        Piece* promotedPiece = PieceFactory::createFigure(currentPlayer, move.promotionType);
        board.set(toRow, toCol, promotedPiece);
    }
    else {

        board.set(toRow, toCol, piece, fromRow, fromCol);

    }
    
    updateCastlingRights(fromRow, fromCol, toRow, toCol);
    updateEnPassant(fromRow, fromCol, toRow, toCol);
   

    // Switch player and update timer
    switchPlayer();
    

    updateGameState();
    addToHistory();

    return true;
}

bool Game::isValidMove(int fromRow, int fromCol, int toRow, int toCol) const {
    // Bounds checking
    if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    Piece* piece = board.get(fromRow, fromCol);
    if (!piece || piece->getColor() != currentPlayer) {
        return false;
    }

    // Check if the piece can make this move
    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, board)) {
        // Special case: castling
        if (piece->getType() == Type::KING && abs(toCol - fromCol) == 2) {
            return canCastle(currentPlayer, toCol > fromCol);
        }
        // Special case: en passant
        if (piece->getType() == Type::PAWN && isEnPassantValid(fromRow, fromCol, toRow, toCol)) {
            return true;
        }
        return false;
    }

    // Check if this move would leave the king in check
    return simulateMove(fromRow, fromCol, toRow, toCol);
}

bool Game::isInCheck(Colour color) const {
    // Find the king
    int kingRow = -1, kingCol = -1;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.get(row, col);
            if (piece && piece->getType() == Type::KING && piece->getColor() == color) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    if (kingRow == -1) return false; // No king found

    return isSquareUnderAttack(kingRow, kingCol, (color == Colour::WHITE) ? Colour::BLACK : Colour::WHITE);
}

bool Game::isInCheckmate(Colour color) const {
    if (!isInCheck(color)) return false;
    return !hasValidMoves(color);
}

bool Game::isInStalemate(Colour color) const {
    if (isInCheck(color)) return false;
    return !hasValidMoves(color);
}

bool Game::canCastle(Colour color, bool kingside) const {
    int row = (color == Colour::WHITE) ? 7 : 0;

    // Check if king or rook has moved
    if (color == Colour::WHITE) {
        if (whiteKingMoved) return false;
        if (kingside && whiteRookKingsideMoved) return false;
        if (!kingside && whiteRookQueensideMoved) return false;
    }
    else {
        if (blackKingMoved) return false;
        if (kingside && blackRookKingsideMoved) return false;
        if (!kingside && blackRookQueensideMoved) return false;
    }

    // Check if king is in check
    if (isInCheck(color)) return false;

    // Check if path is clear and squares are not under attack
    Colour opponent = (color == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;

    if (kingside) {
        // Check squares between king and rook
        if (board.get(row, 5) || board.get(row, 6)) return false;
        // Check if squares king passes through are under attack
        if (isSquareUnderAttack(row, 5, opponent) || isSquareUnderAttack(row, 6, opponent)) return false;
    }
    else {
        // Check squares between king and rook
        if (board.get(row, 1) || board.get(row, 2) || board.get(row, 3)) return false;
        // Check if squares king passes through are under attack
        if (isSquareUnderAttack(row, 2, opponent) || isSquareUnderAttack(row, 3, opponent)) return false;
    }

    return true;
}

bool Game::performCastling(Colour color, bool kingside) {
    if (!canCastle(color, kingside)) return false;

    int row = (color == Colour::WHITE) ? 7 : 0;

    Piece* king = board.get(row, 4);
    Piece* rook = board.get(row, kingside ? 7 : 0);

    if (kingside) {
        board.set(row, 6, king);
        board.set(row, 5, rook);
        board.set(row, 4, nullptr);
        board.set(row, 7, nullptr);
    }
    else {
        board.set(row, 2, king);
        board.set(row, 3, rook);
        board.set(row, 4, nullptr);
        board.set(row, 0, nullptr);
    }

    return true;
}

bool Game::isEnPassantValid(int fromRow, int fromCol, int toRow, int toCol) const {
    if (enPassantTargetRow != toRow || enPassantTargetCol != toCol) {
        return false;
    }

    Piece* piece = board.get(fromRow, fromCol);
    if (!piece || piece->getType() != Type::PAWN) {
        return false;
    }

    // Check if it's a valid en passant capture
    int direction = (piece->getColor() == Colour::WHITE) ? -1 : 1;
    return (toRow == fromRow + direction && abs(toCol - fromCol) == 1);
}

Type Game::getPromotionChoice() const {
    std::wcout << L"Pawn promotion! Choose piece (Q/R/B/N): ";
    wchar_t wchoice;
    std::wcin >> wchoice;

    char choice = char(wchoice);

    switch (toupper(choice)) {
    case 'R': return Type::ROOK;
    case 'B': return Type::BISHOP;
    case 'N': return Type::KNIGHT;
    default: return Type::QUEEN;
    }
}

Vector<std::pair<int, int>> Game::getAllValidMoves(Colour color) const {
    Vector<std::pair<int, int>> validMoves;

    for (int fromRow = 0; fromRow < 8; ++fromRow) {
        for (int fromCol = 0; fromCol < 8; ++fromCol) {
            Piece* piece = board.get(fromRow, fromCol);
            if (!piece || piece->getColor() != color) continue;

            for (int toRow = 0; toRow < 8; ++toRow) {
                for (int toCol = 0; toCol < 8; ++toCol) {
                    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
                        validMoves.push_back({ fromRow * 8 + fromCol, toRow * 8 + toCol });
                    }
                }
            }
        }
    }

    return validMoves;
}

bool Game::hasValidMoves(Colour color) const {
    for (int fromRow = 0; fromRow < 8; ++fromRow) {
        for (int fromCol = 0; fromCol < 8; ++fromCol) {
            Piece* piece = board.get(fromRow, fromCol);
            if (!piece || piece->getColor() != color) continue;

            for (int toRow = 0; toRow < 8; ++toRow) {
                for (int toCol = 0; toCol < 8; ++toCol) {
                    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::isGameOver() const {
    return gameState == GameState::CHECKMATE ||
        gameState == GameState::STALEMATE ||
        gameState == GameState::DRAW_BY_REPETITION ||
        gameState == GameState::DRAW_BY_INSUFFICIENT_MATERIAL;
}

// Helper methods implementation

bool Game::isSquareUnderAttack(int row, int col, Colour attacker) const {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board.get(r, c);
            if (piece && piece->getColor() == attacker) {
                if (piece->isValidMove(r, c, row, col, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::updateGameState() {

    if (isInCheck(currentPlayer)) {
        if (isInCheckmate(currentPlayer)) {
            gameState = GameState::CHECKMATE;
        }
        else {
            gameState = GameState::CHECK;
        }
    }
    else if (isInStalemate(currentPlayer)) {
        gameState = GameState::STALEMATE;
    }
    else if (isDrawByRepetition()) {
        gameState = GameState::DRAW_BY_REPETITION;
    }
    else if (isDrawByInsufficientMaterial()) {
        gameState = GameState::DRAW_BY_INSUFFICIENT_MATERIAL;
    }
    else {
        gameState = GameState::PLAYING;
    }
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}

String Game::parseAlgebraicNotation(const String& move, int& fromRow, int& fromCol, int& toRow, int& toCol) const {
    if (move.getSize() < 4) return "Move too short";

    // Simple format: "e2 e4" or "e2e4"
    String from, to;
    if (move.getSize() == 5 && move[2] == ' ') {
        from = move.substr(0, 2);
        to = move.substr(3, 2);
    }
    else if (move.getSize() == 4) {
        from = move.substr(0, 2);
        to = move.substr(2, 2);
    }
    else {
        return "Invalid format";
    }

    // Convert algebraic to array indices
    if (from.getSize() != 2 || to.getSize() != 2) return "Invalid coordinates";

    fromCol = from[0] - 'a';
    fromRow = 8 - (from[1] - '0');
    toCol = to[0] - 'a';
    toRow = 8 - (to[1] - '0');

    if (fromCol < 0 || fromCol >= 8 || fromRow < 0 || fromRow >= 8 ||
        toCol < 0 || toCol >= 8 || toRow < 0 || toRow >= 8) {
        return "Coordinates out of bounds";
    }

    return "";
}

void Game::addToHistory() {
    gameHistory.push_back(boardToString());
}

bool Game::simulateMove(int fromRow, int fromCol, int toRow, int toCol) const {
    // Create a temporary copy of the board
    Board tempBoard = board;

    // Get the moving piece from the temporary board
    Piece* movingPiece = tempBoard.get(fromRow, fromCol);

    // Make the move on the temporary board
    tempBoard.set(toRow, toCol, movingPiece, fromRow, fromCol);

    // Check if the king would be in check after this move
    bool inCheck = isInCheck(movingPiece->getColor(), tempBoard);

    return !inCheck;
}

bool Game::isInCheck(Colour kingColor, const Board& boardToCheck) const {
    // If checking the current board, just use the existing function
    if (&boardToCheck == &board) {
        return isInCheck(kingColor);
    }

    // Temporarily swap the board to reuse existing logic
    Board* originalBoard = const_cast<Board*>(&board);
    Board savedBoard = *originalBoard;
    *originalBoard = boardToCheck;

    // Use the existing isInCheck function
    bool result = isInCheck(kingColor);

    // Restore the original board
    *originalBoard = savedBoard;

    return result;
}

void Game::updateCastlingRights(int fromRow, int fromCol, int toRow, int toCol) {
    Piece* piece = board.get(toRow, toCol);
    if (!piece) return;

    if (piece->getType() == Type::KING) {
        if (piece->getColor() == Colour::WHITE) {
            whiteKingMoved = true;
        }
        else {
            blackKingMoved = true;
        }
    }
    else if (piece->getType() == Type::ROOK) {
        if (piece->getColor() == Colour::WHITE) {
            if (fromRow == 7 && fromCol == 0) whiteRookQueensideMoved = true;
            if (fromRow == 7 && fromCol == 7) whiteRookKingsideMoved = true;
        }
        else {
            if (fromRow == 0 && fromCol == 0) blackRookQueensideMoved = true;
            if (fromRow == 0 && fromCol == 7) blackRookKingsideMoved = true;
        }
    }
}

void Game::updateEnPassant(int fromRow, int fromCol, int toRow, int toCol) {
    // Reset en passant target
    enPassantTargetRow = -1;
    enPassantTargetCol = -1;

    Piece* piece = board.get(toRow, toCol);
    if (piece && piece->getType() == Type::PAWN) {
        // Check if pawn moved two squares
        if (abs(toRow - fromRow) == 2) {
            enPassantTargetRow = (fromRow + toRow) / 2;
            enPassantTargetCol = toCol;
        }
    }
}

String Game::boardToString() const {
    String result;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.get(row, col);
            if (piece) {
                // Convert integers to characters and append
                result += char('0' + static_cast<int>(piece->getType()));
                result += char('0' + static_cast<int>(piece->getColor()));
            }
            else {
                result += "99";
            }
        }
    }
    return result;
}

bool Game::isDrawByRepetition() const {
    if (gameHistory.size() < 6) return false; // Need at least 3 repetitions

    String currentPosition = gameHistory.back();
    int count = 0;

    for (const auto& position : gameHistory) {
        if (position == currentPosition) {
            count++;
        }
    }

    return count >= 3;
}

bool Game::isDrawByInsufficientMaterial() const {
    Vector<Piece*> whitePieces, blackPieces;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.get(row, col);
            if (piece) {
                if (piece->getColor() == Colour::WHITE) {
                    whitePieces.push_back(piece);
                }
                else {
                    blackPieces.push_back(piece);
                }
            }
        }
    }

    // King vs King
    if (whitePieces.size() == 1 && blackPieces.size() == 1) {
        return true;
    }

    // King and Bishop vs King or King and Knight vs King
    if ((whitePieces.size() == 2 && blackPieces.size() == 1) ||
        (whitePieces.size() == 1 && blackPieces.size() == 2)) {

        Vector<Piece*>& largerSide = (whitePieces.size() == 2) ? whitePieces : blackPieces;

        for (Piece* piece : largerSide) {
            if (piece->getType() == Type::BISHOP || piece->getType() == Type::KNIGHT) {
                return true;
            }
        }
    }

    // King and Bishop vs King and Bishop (same colored squares)
    if (whitePieces.size() == 2 && blackPieces.size() == 2) {
        bool whiteBishop = false, blackBishop = false;
        int whiteBishopSquare = -1, blackBishopSquare = -1;

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Piece* piece = board.get(row, col);
                if (piece && piece->getType() == Type::BISHOP) {
                    if (piece->getColor() == Colour::WHITE) {
                        whiteBishop = true;
                        whiteBishopSquare = (row + col) % 2;
                    }
                    else {
                        blackBishop = true;
                        blackBishopSquare = (row + col) % 2;
                    }
                }
            }
        }

        if (whiteBishop && blackBishop && whiteBishopSquare == blackBishopSquare) {
            return true;
        }
    }

    return false;
}

bool Game::saveGame(const String& filename) const {
    std::ofstream file(filename.c_str());
    if (!file.is_open()) return false;

    // Save board state
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.get(row, col);
            if (piece) {
                file << static_cast<int>(piece->getType()) << " "
                    << static_cast<int>(piece->getColor()) << " ";
            }
            else {
                file << "9 9 ";
            }
        }
        file << "\n";
    }

    // Save game state
    file << static_cast<int>(currentPlayer) << "\n";
    file << static_cast<int>(gameState) << "\n";

    // Save castling rights
    file << whiteKingMoved << " " << blackKingMoved << " "
        << whiteRookKingsideMoved << " " << whiteRookQueensideMoved << " "
        << blackRookKingsideMoved << " " << blackRookQueensideMoved << "\n";

    // Save en passant
    file << enPassantTargetRow << " " << enPassantTargetCol << "\n";

    // Save move history count

    return true;
}

bool Game::loadGame(const String& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) return false;

    // Clear current board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            //delete board.get(row, col);
            board.set(row, col, nullptr);
        }
    }

    // Load board state
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int pieceType, pieceColor;
            file >> pieceType >> pieceColor;
            if (pieceType != 9) {
                Colour color = static_cast<Colour>(pieceColor);
                Type type = static_cast<Type>(pieceType);
                Piece* piece = PieceFactory::createFigure(color, type);
                board.set(row, col, piece);
            }
        }
    }

    // Load game state
    int player, state;
    file >> player >> state;
    currentPlayer = static_cast<Colour>(player);
    gameState = static_cast<GameState>(state);

    // Load castling rights
    file >> whiteKingMoved >> blackKingMoved
        >> whiteRookKingsideMoved >> whiteRookQueensideMoved
        >> blackRookKingsideMoved >> blackRookQueensideMoved;

    // Load en passant
    file >> enPassantTargetRow >> enPassantTargetCol;

    return true;
}
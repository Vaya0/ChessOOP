#pragma once
#include <iostream>
#include "String.h"
#include "Board.h"
#include <fstream>
#include "Vector.hpp"

enum class GameState {
	PLAYING,
	CHECK,
	CHECKMATE,
	STALEMATE,
	DRAW_BY_REPETITION,
	DRAW_BY_INSUFFICIENT_MATERIAL,
};

struct Move {
	int fromRow, fromCol;
	int toRow, toCol;
	Piece* capturedPiece = nullptr;
	bool isEnPassant = false;
	bool isCastling = false;
	bool isPromotion = false;
	Type promotionType = Type::QUEEN;

	Move(int fr, int fc, int tr, int tc)
		: fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {
	}
};

class Game {
private:
    Board board;
    Colour currentPlayer;
    GameState gameState;
    Vector<String> gameHistory;// for draw by repetition

    // Special move tracking
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookKingsideMoved = false;
    bool whiteRookQueensideMoved = false;
    bool blackRookKingsideMoved = false;
    bool blackRookQueensideMoved = false;

    // En passant tracking
    int enPassantTargetRow = -1;
    int enPassantTargetCol = -1;

public:
    Game();


    // Core game methods
    bool makeMove(const String& moveStr);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);

    // Game state methods
    GameState getGameState() const;
    Colour getCurrentPlayer() const;
    bool isGameOver() const;

    // Move validation
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isInCheck(Colour color) const;
    bool isInCheckmate(Colour color) const;
        bool isInCheck(Colour kingColor, const Board& boardToCheck) const;

    bool isInStalemate(Colour color) const;

    // Special moves
    bool canCastle(Colour color, bool kingside) const;
    bool performCastling(Colour color, bool kingside);
    bool isEnPassantValid(int fromRow, int fromCol, int toRow, int toCol) const;
    Type getPromotionChoice() const;

    // Utility methods
    Vector<std::pair<int, int>> getAllValidMoves(Colour color) const;
    bool hasValidMoves(Colour color) const;
    String boardToString() const;

    bool isDrawByRepetition() const;
    bool isDrawByInsufficientMaterial() const;

    // File I/O
    bool saveGame(const String& filename) const;
    bool loadGame(const String& filename);

    const Board& getBoard() const { return board; }

private:
    bool isSquareUnderAttack(int row, int col, Colour attacker) const;
    void updateGameState();
    void switchPlayer();
    String parseAlgebraicNotation(const String& move, int& fromRow, int& fromCol, int& toRow, int& toCol) const;
    void addToHistory();
    bool simulateMove(int fromRow, int fromCol, int toRow, int toCol) const;
    void updateCastlingRights(int fromRow, int fromCol, int toRow, int toCol);
    void updateEnPassant(int fromRow, int fromCol, int toRow, int toCol);
};


#include "ChessDisplay.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "String"

using namespace std;

bool ChessDisplay::setupUnicodeConsole() {
    if (!SetConsoleOutputCP(CP_UTF8) || !SetConsoleCP(CP_UTF8)) {
        return false;
    }

    setlocale(LC_ALL, "");

    // Enable UTF-16 mode for wide character output
    int result1 = _setmode(_fileno(stdout), _O_U16TEXT);
    int result2 = _setmode(_fileno(stderr), _O_U16TEXT);

    if (result1 == -1 || result2 == -1) {
        return false;
    }

    // Unicode-compatible font
    CONSOLE_FONT_INFOEX cfi = {};
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = 20;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

        wcscpy_s(cfi.FaceName, L"MS Gothic");

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!SetCurrentConsoleFontEx(hOut, FALSE, &cfi)) {
            wcscpy_s(cfi.FaceName, L"Consolas");
            SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
        }

        return true;
    }

    // Set text color in Windows CMD
    void ChessDisplay::setColor(int textColor, int bgColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
    }

    void ChessDisplay::displayBoard(const Game& game) {
        const Board& board = game.getBoard();
        if (board.get(4, 4) == nullptr) { wcout << L"  ============\n\n"; }
        // White's view
        wcout << L"\n  White's View\n";
        wcout << L"  ============\n\n";

        for (int displayRow = 0; displayRow < 8; displayRow++) {
            int boardRow = displayRow;  
            int rowLabel = 8 - displayRow;  

            wcout << rowLabel << L" ";

            for (int displayCol = 0; displayCol < 8; displayCol++) {
                int boardCol = displayCol;  

                bool isLightSquare = (boardRow + boardCol) % 2 == 0;

                if (isLightSquare) {
                    setColor(0, 7); 
                }
                else {
                    setColor(15, 0); 
                }

                Piece* piece = board.get(boardRow, boardCol);
                if (piece) {
                    wcout << piece->getSymbol() << L" ";
                }
                else {
                    wcout << L"  ";
                }
            }

            setColor(15, 0); // Reset color
            wcout << L"\n";
        }

        wcout << L"  ";
        for (char c = 'a'; c <= 'h'; ++c) {
            wcout << c << L" ";
        }
        wcout << L"\n";

        // Black's view
        wcout << L"\n  Black's View\n";
        wcout << L"  ============\n\n";

        for (int displayRow = 0; displayRow < 8; displayRow++) {
            int boardRow = 7 - displayRow;  // Reversed array row index
            int rowLabel = displayRow + 1;  

            wcout << rowLabel << L" ";

            for (int displayCol = 0; displayCol < 8; displayCol++) {
                int boardCol = 7 - displayCol;  

                bool isLightSquare = (boardRow + boardCol) % 2 == 0;

                if (isLightSquare) {

                    setColor(0, 7);
                }
                else {
                    setColor(15, 0);
                }

                Piece* piece = board.get(boardRow, boardCol);
                if (piece) {
                    wcout << piece->getSymbol() << L" ";
                }
                else {
                    wcout << L"  ";
                }
            }

            setColor(15, 0); // Reset color
            wcout << L"\n";
        }

        wcout << L"  ";
        for (char c = 'h'; c >= 'a'; --c) {
            wcout << c << L" ";
        }
        wcout << L"\n";
    }

    void ChessDisplay::displayGameInfo(const Game& game) {
        wcout << L"Current player: " << (game.getCurrentPlayer() == Colour::WHITE ? L"White" : L"Black") << L"\n";

        switch (game.getGameState()) {
        case GameState::PLAYING:
            wcout << L"Status: Playing\n";
            break;
        case GameState::CHECK:
            wcout << L"Status: Check!\n";
            break;
        case GameState::CHECKMATE:
            wcout << L"Status: Checkmate! "
                << (game.getCurrentPlayer() == Colour::WHITE ? L"Black" : L"White")
                << L" wins!\n";
            break;
        case GameState::STALEMATE:
            wcout << L"Status: Stalemate - Draw!\n";
            break;
        case GameState::DRAW_BY_REPETITION:
            wcout << L"Status: Draw by repetition!\n";
            break;
        case GameState::DRAW_BY_INSUFFICIENT_MATERIAL:
            wcout << L"Status: Draw by insufficient material!\n";
            break;
        }
        wcout << L"\n";
    }

    // input from user
    String ChessDisplay::getMoveInput() {
        if (_setmode(_fileno(stdin), _O_TEXT) == -1) {
            wcerr << L"Failed to set mode for stdin.\n";
            return ""; 
        }        
        wcout << L"Enter move ('e2e4' or 'help'): ";

        wstring wmove;
        wcin >> wmove;

        String move = String(wmove.begin(), wmove.end());

        if (_setmode(_fileno(stdin), _O_U16TEXT) == -1) {
            wcerr << L"Failed to set mode for stdin.\n";
            return ""; 
        }

        return move;
    }

    // error message
    void ChessDisplay::displayError(const String& message) {
        wcout << L"Error: ";
        for (size_t i = 0; i < message.getSize(); ++i) {
            wcout << static_cast<wchar_t>(message[i]);
        }
        wcout << L"\n";
    }

    void ChessDisplay::displayMessage(const String& message) {
        for (size_t i = 0; i < message.getSize(); ++i) {
            wcout << static_cast<wchar_t>(message[i]);
        }
        wcout << L"\n";
    }




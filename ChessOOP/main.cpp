#include "Play.h"
#include <iostream>
#include "ChessDisplay.h"
#include "String"

using namespace std;

void static handleGameEnd(Game& game, ChessDisplay& display) {
    if (game.isGameOver()) {
        system("cls");
        display.displayBoard(game);
        display.displayGameInfo(game);
        display.displayMessage("Game Over!");
    }
    display.displayMessage("Thanks for playing!");
    wcout << L"Press Enter to exit...";
    wcin.get();
}

bool static processInput(const String& input, Game& game, ChessDisplay& display, bool& gameRunning) {
    if (input == "quit" || input == "exit") {
        gameRunning = false;
        return true;
    }
    else if (input == "save") {
        display.displayMessage("Enter filename: ");
        String filename = display.getMoveInput();
        if (game.saveGame(String(filename.c_str()))) {
            display.displayMessage("Game saved successfully!");
        }
        else {
            display.displayError("Failed to save game!");
        }
        return true;
    }
    else if (input == "load") {
        display.displayMessage("Enter filename: ");
        String filename = display.getMoveInput();
        if (game.loadGame(String(filename.c_str()))) {
            display.displayMessage("Game loaded successfully!");
        }
        else {
            display.displayError("Failed to load game!");
        }
        return true;
    }
    else if (input == "help") {
        display.displayMessage("Commands:");
        display.displayMessage("- Move: e2e4 (from, to)");
        display.displayMessage("- save: Save game");
        display.displayMessage("- load: Load game");
        display.displayMessage("- quit: Exit game");

        wcout << L"Press Enter to continue...";
        wcin.get();
        return true;
    }
    else {
        if (!game.makeMove(String(input.c_str()))) {
            display.displayError("Invalid move! Try again.");
            wcout << L"Press Enter to continue...";
            wcin.get();
            return false; 
        }
        return true; 
    }
}

int main() {
    ChessDisplay display;
    display.setupUnicodeConsole();

    Game game;
    bool gameRunning = true;

    while (gameRunning && !game.isGameOver()) {
        system("cls");

        display.displayBoard(game);
        display.displayGameInfo(game);

        String input = display.getMoveInput();
        processInput(input, game, display, gameRunning);
    }

    handleGameEnd(game, display);
    return 0;
}
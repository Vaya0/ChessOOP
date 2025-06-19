#include "GameHandler.h"  

int main() {
    ChessDisplay display;
    display.setupUnicodeConsole();

    Game game;
    runGameLoop(game, display);

    return 0;
}
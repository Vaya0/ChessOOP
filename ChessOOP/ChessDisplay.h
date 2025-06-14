#include "Play.h"

using namespace std;

class ChessDisplay {
public:
    ChessDisplay() {}
    bool setupUnicodeConsole();

    // Set text color in Windows CMD
    void setColor(int textColor, int bgColor);

    void displayBoard(const Game& game);

    void displayGameInfo(const Game& game);

    // input from user
    String getMoveInput();

    // error message
    void displayError(const String& message);

    // message
    void displayMessage(const String& message);
};



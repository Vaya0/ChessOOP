#include "Play.h"







bool Play::isMoveCommandValid(String move)
{
	if (move != "move" || move != "save" || move != "continue" || move != "exit") {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	else if (move == "move") {
		String coordinates;
		std::cin >> coordinates;
		if(move[0] < 'a' || move[0] > 'h' || move[1] < '1' || move[1] > '8' || move[2] != ' ' 
			|| move[3] < 'a' || move[3] > 'h' || move[4] < '1' || move[4] > '8')
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	return true;
}

void Play::startGame()
{
	String command;

	while (true)
	{
		//change player every turn
		if (player == 1) {
			player = 2;
		}
		else {
			player = 1;
		}

		PrintBoard(board);//printing after each move

		std::cout << std::endl;
		std::cout << "Player " << player << " playing. Enter command here(to open help menu enter 'help'):" << std::endl;

		//make a command that prints the list of commands for the user

		std::cin >> command;
		if (command == "help") {
			std::cout << "-----------------Help menu-----------------" << std::endl;
			std::cout << "Commands: " << std::endl;
			std::cout << "exit -> exits the game." << std::endl;
			std::cout << "save -> saves the game to a file." << std::endl;
			std::cout << "continue -> resumes a game from a file." << std::endl;
			std::cout << "move -> if possible, move the figure from position (x1, y1) to position (x2, y2)" << std::endl;
			std::cout << "x1y1 x2y2 -> enter coordinates after using move command." << std::endl;
			std::cout << "example move command ---> move " << std::endl<<"e2 e4" << std::endl;
			if (player == 1) {
				player = 2;
			}
			else {
				player = 1;
			}
		}
		else if (command == "exit") {
			break;
		}
		else {
			while (!(canMove(command, board, player)) || (!(isMoveCommandValid(command))))
			{
				std::cout << "Please enter your move again!" << std::endl;
				std::cin >> command;
			}
		}
		if (isKingDead) {
			std::cout << "Player " << player << " wins!" << std::endl;
			break;
		}
	}
}
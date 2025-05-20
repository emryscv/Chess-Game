#include <GLFW/glfw3.h>
#include "Board.h"
#include "iostream"

int main(void)
{
	Board board;

	for (;;) {
		system("cls");
		board.PrintBoard();

		std::cout << "Current Turn: " << (board.GetTurn() == Color::White ? "White" : "Black") << "\n";
		if (board.GetIsCheck()) std::cout << "Check\n";

		int originX;
		int originY;
		int destinationX;
		int destinationY;
		bool invalid = true;
		while (invalid) {
			std::cout << "Select a piece\n";
			std::cout << "Enter row: ";
			std::cin >> originX;
			std::cout << "Enter col: ";
			std::cin >> originY;
			if (Board::ValidCoordinates(originX, originY) and board.GetPosition(originX, originY) != nullptr and board.GetPosition(originX, originY)->GetColor() == board.GetTurn()) invalid = false;
			else {
				std::cout << "Not one of your pieces!!\n";
			}
		}

		invalid = true;
		while (invalid) {
			std::cout << "Select a destination\n";
			std::cout << "Enter row: ";
			std::cin >> destinationX;
			std::cout << "Enter col: ";
			std::cin >> destinationY;
			if (board.IsValidMove(originX, originY, destinationX, destinationY)) invalid = false;
			else {
				std::cout << "Not a valid move!!\n"; 
			}
		}

		board.Move(originX, originY, destinationX, destinationY);
		
		if (board.GetIsCheck()) board.SetCheck(false);

		if (board.IsCheck(board.GetTurn() == Color::White ? Color::Black : Color::White)) {
			board.SetCheck(true);
		}
		board.SwitchTurn();
	}
	return 0;
}
#include <iostream>
#include "Chessboard.cpp"
int main(int argc, char** argv) {
	if (argc == 3) {
		Chessboard board = Chessboard('W');
		bool gameEnd = false;
		// If there hasnt been a checkmate or resignation
		while (!gameEnd) {
			// If it is the computers turn
			if ((board.GetMove() && argv[1][0] == 'W') || (!board.GetMove() && argv[1][0] == 'B')) {
				// Computer Move
				board.FlipMove();

			// Players Turn
			} else {
				std::cout << "Enter Move. Format goes like A1 A3," << std::endl;
				std::cout << "Where it is the starting square to the final square." << std::endl;
				std::cout << "Move: ";
				std::string inMove;
				std::cin >> inMove;
				std::cout << std::endl;
				board.FlipMove();
			}
		}
		return 1;
	} else {
		std::cerr << "Error: Wrong Number Of Arguments Entered." << std::endl;
		std::cerr << argc << " Entered, 3 Required" << std::endl;
		return -1;
	}
	return 1;
}

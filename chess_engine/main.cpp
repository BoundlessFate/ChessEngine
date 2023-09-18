#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <climits>
#include <cassert>
#include "Engine.cpp"
int main(int argc, char** argv) {
	srand(time(NULL));
	// Arguments should be entered like so:  ./main.out [W/B] [Engine Depth]
	if (argc == 3) {
		// Currently not doing anything about time per move
		Chessboard board(argv[1][0]);
		bool gameEnd = false;
		// If there hasnt been a checkmate or resignation
		std::string lastMove = "";
		int stalemateCounter = 0;
		while (!gameEnd) {
			board.DisplayBoard();
			// If it is the computers turn
			if ((board.GetMove() && argv[1][0] == 'W') || (!board.GetMove() && argv[1][0] == 'B')) {
				// Computer Move
				std::cout << "Computer Is Making Move..." << std::endl;
				std::vector<std::string> allMoves = board.CheckValidMoves(lastMove);
				allMoves = PinsAndChecks(allMoves, board);
				if (allMoves.size() == 0 || stalemateCounter >= 100) {
					gameEnd = true;
					if (stalemateCounter < 100 && CheckmateCheck(board, lastMove))
						std::cout << "BOT HAS LOST BY CHECKMATE 1-0" << std::endl;
					else
						std::cout << "STALEMATE 1/2-1/2" << std::endl;
					continue;
				}
				std::string computerMove = FindBestMove(board, allMoves, lastMove, argv[2]);
				board.ProcessMove(computerMove);
				lastMove = computerMove;
				std::cout << computerMove << std::endl;
				board.FlipMove();
				std::cout << "--------------------------" << std::endl;
				// Players Turn
			} else {
				std::vector<std::string> allMoves = board.CheckValidMoves(lastMove);
				allMoves = PinsAndChecks(allMoves, board);
				if (allMoves.size() == 0 || stalemateCounter >= 100) {
					gameEnd = true;
					if (stalemateCounter < 100 && CheckmateCheck(board, lastMove))
						std::cout << "PLAYER HAS LOST BY CHECKMATE 0-1" << std::endl;
					else
						std::cout << "STALEMATE 1/2-1/2" << std::endl;
					continue;
				}
				std::string inMove;
				while(true) {
					std::cout << "Enter Move. Format goes like Pe2 e4," << std::endl;
					std::cout << "Where it is the starting square to the final square." << std::endl;
					std::cout << "Move: ";
					// For human play
					getline(std::cin,inMove);
					// For bot on bot play
					/* inMove = FindBestMove(board, allMoves); */
					std::cout << inMove << std::endl;
					bool found = false;
					for (unsigned int i=0; i<allMoves.size(); i++) {
						if (inMove == allMoves[i]) {
							found = true;
							break;
						}
					}
					if (found)
						break;
					std::cout << "Error: Incorrect Move Inputted... Try Again." << std::endl;
				}
				board.ProcessMove(inMove);
				lastMove = inMove;
				board.FlipMove();
				// If the board should be cleared
				std::cout << std::flush;
				system("clear");
			}
			stalemateCounter += 1;
			if (lastMove[lastMove.size() - 3] == 'x')
				stalemateCounter = 0;
		}
		return 1;
	} else {
		std::cerr << "Error: Wrong Number Of Arguments Entered." << std::endl;
		std::cerr << argc << " Entered, 3 Required" << std::endl;
		return -1;
	}
	return 1;
}

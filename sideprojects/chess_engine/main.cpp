#include <iostream>
#include "Chessboard.cpp"
#include <stdlib.h>
#include <time.h>
#include <climits>
std::vector<std::string> PinsAndChecks(std::vector<std::string> allMoves, Chessboard& board) {
	std::vector<std::string> trueMoves;
	for (unsigned int i=0; i<allMoves.size(); i++) {
		// Create a duplicate board
		Chessboard newBoard(board);
		newBoard.ProcessMove(allMoves[i]);
		// Find where the king for the current player is
		char file = '*';
		int rank = -1;
		bool found = false;
		for (unsigned int j=0; j<8; j++) {
			for (unsigned int k=0; k<8; k++) {
				Piece* currentPiece = newBoard.GetPiece(files[j], k);
				if (currentPiece->GetType() == 'K' && ((currentPiece->GetColor() == 'W' && board.GetMove())
							|| (currentPiece->GetColor() == 'B' && !board.GetMove()))) {
					file = files[j];
					rank = 8-k;
					found = true;
					break;
				}
			}
			if (found)
				break;
		}
		newBoard.FlipMove();
		std::vector<std::string> opponentMoves = newBoard.CheckValidMoves(allMoves[i]);
		bool badMoveFound = false;
		for (unsigned int j=0; j<opponentMoves.size(); j++) {
			// If illegal move found
			char rankChar = '0' + char(rank);
			if (opponentMoves[j][opponentMoves.size()-2] == file && opponentMoves[j][opponentMoves.size()-1] == rankChar) {
				badMoveFound = true;
				break;
			}
		}
		if (!badMoveFound)
			trueMoves.push_back(allMoves[i]);
	}
	return trueMoves;
}
// This will only run after the game ends (to determine how it ended)
bool CheckmateCheck(Chessboard& board, std::string lastMove) {
	// Find where the king for the current player is
	char file = '*';
	int rank = -1;
	bool found = false;
	for (unsigned int j=0; j<8; j++) {
		for (unsigned int k=0; k<8; k++) {
			Piece* currentPiece = board.GetPiece(files[j], k);
			if (currentPiece->GetType() == 'K' && ((currentPiece->GetColor() == 'W' && board.GetMove())
						|| (currentPiece->GetColor() == 'B' && !board.GetMove()))) {
				file = files[j];
				rank = 8-k;
				found = true;
				break;
			}
		}
		if (found)
			break;
	}
	board.FlipMove();
	std::vector<std::string> opponentMoves = board.CheckValidMoves(lastMove);
	for (unsigned int j=0; j<opponentMoves.size(); j++) {
		// If opponent can capture king
		char rankChar = '0' + char(rank);
		if (opponentMoves[j].find({file, rankChar}) != std::string::npos)
			return true;
	}
	// Return false if stalemate
	return false;
}
int main(int argc, char** argv) {
	srand(time(NULL));
	// Arguments should be entered like so:  ./main.out [W/B] [Time Per Move]
	if (argc == 3) {
		// Currently not doing anything about time per move
		Chessboard board(argv[1][0]);
		bool gameEnd = false;
		// If there hasnt been a checkmate or resignation
		std::string lastMove = "";
		while (!gameEnd) {
			// If it is the computers turn
			if ((board.GetMove() && argv[1][0] == 'W') || (!board.GetMove() && argv[1][0] == 'B')) {
				// Computer Move
				std::cout << "Computer Is Making Move..." << std::endl;
				std::vector<std::string> allMoves = board.CheckValidMoves(lastMove);
				allMoves = PinsAndChecks(allMoves, board);
				if (allMoves.size() == 0) {
					gameEnd = true;
					if (CheckmateCheck(board, lastMove))
						std::cout << "BOT HAS LOST BY CHECKMATE 1-0" << std::endl;
					else
						std::cout << "STALEMATE 1/2-1/2" << std::endl;
					continue;
				}
				std::cout << "*****" << std::endl;
				std::cout << "ALL VALID COMPUTER MOVES" << std::endl;
				for (unsigned int i=0; i< allMoves.size(); i++) {
					std::cout << allMoves[i] << std::endl;
				}
				std::cout << "*****" << std::endl;
				int moveNum = rand() % allMoves.size();
				board.ProcessMove(allMoves[moveNum]);
				lastMove = allMoves[moveNum];
				std::cout << allMoves[moveNum] << std::endl;
				board.FlipMove();
				std::cout << "--------------------------" << std::endl;

				// Players Turn
			} else {
				board.DisplayBoard();
				std::vector<std::string> allMoves = board.CheckValidMoves(lastMove);
				for (unsigned int i=0; i< allMoves.size(); i++) {
					std::cout << allMoves[i] << std::endl;
				}
				allMoves = PinsAndChecks(allMoves, board);
				std::cout << "*****" << std::endl;
				std::cout << "ALL VALID PLAYER MOVES" << std::endl;
				for (unsigned int i=0; i< allMoves.size(); i++) {
					std::cout << allMoves[i] << std::endl;
				}
				std::cout << "*****" << std::endl;
				if (allMoves.size() == 0) {
					gameEnd = true;
					if (CheckmateCheck(board, lastMove))
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

					/* getline(std::cin,inMove); */
					inMove = allMoves[rand() % allMoves.size()];
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
				/* std::cout << std::flush; */
				/* system("clear"); */
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

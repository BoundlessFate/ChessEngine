#include "Chessboard.h"
Chessboard::Chessboard() {
	for (unsigned int i=0; i<8; i++) {
		data.push_back(std::vector<Piece*>());
	}
	data[0][0] = new Piece('R', 'B');
	data[0][1] = new Piece('N', 'B');
	data[0][2] = new Piece('B', 'B');
	data[0][3] = new Piece('Q', 'B');
	data[0][4] = new Piece('K', 'B');
	data[0][5] = new Piece('B', 'B');
	data[0][6] = new Piece('N', 'B');
	data[0][7] = new Piece('R', 'B');
	data[1][0] = new Piece('P', 'B');
	data[1][1] = new Piece('P', 'B');
	data[1][2] = new Piece('P', 'B');
	data[1][3] = new Piece('P', 'B');
	data[1][4] = new Piece('P', 'B');
	data[1][5] = new Piece('P', 'B');
	data[1][6] = new Piece('P', 'B');
	data[1][7] = new Piece('P', 'B');
	for (unsigned int i=2; i<6; i++) {
		for (unsigned int j=0; j<8; j++) {
			data[i][j] = new Piece('*', 'E');
		}
	}
	data[6][0] = new Piece('P', 'W');
	data[6][1] = new Piece('P', 'W');
	data[6][2] = new Piece('P', 'W');
	data[6][3] = new Piece('P', 'W');
	data[6][4] = new Piece('P', 'W');
	data[6][5] = new Piece('P', 'W');
	data[6][6] = new Piece('P', 'W');
	data[6][7] = new Piece('P', 'W');
	data[7][0] = new Piece('R', 'W');
	data[7][1] = new Piece('N', 'W');
	data[7][2] = new Piece('B', 'W');
	data[7][3] = new Piece('Q', 'W');
	data[7][4] = new Piece('K', 'W');
	data[7][5] = new Piece('B', 'W');
	data[7][6] = new Piece('N', 'W');
	data[7][7] = new Piece('R', 'W');
}
Chessboard::Chessboard(Chessboard& a) {
	for (unsigned int i=0; i<8; i++) {
		data.push_back(std::vector<Piece*>());
	}
	std::vector<std::vector<Piece*>> oldBoard = a.getBoard();
	for (unsigned int i=0; i<8; i++) {
		for (unsigned int j=0; j<8; j++) {
			data[i][j] = new Piece(oldBoard[i][j]->GetType(), oldBoard[i][j]->GetColor());
		}
	}
}
Chessboard::~Chessboard() {
	for (unsigned int i=0; i<8; i++) {
		for (unsigned int j=0; j<8; j++) {
			delete data[i][j];
		}
	}
}
std::vector<std::string> Chessboard::CheckValidMoves() {
	std::vector<char> files = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	std::vector<std::string> possibleMoves;
	for (unsigned int i=0; i<8; i++) {
		for (unsigned int j=0; j<8; j++) {
			char color = data[i][j]->GetColor();
			char type = data[i][j]->GetType();
			// If the piece is a pawn (separate checks since they can only move in one direction)
			if (color == 'W' && type == 'P' && whiteToMove) {
				if (i == 6) {
					// Allow move two spaces if the pawn is on the starting rank and is unobstructed
					if (data[5][j]->GetType() == '*' && data[4][j]->GetType() == '*') {
						std::string line = {type, files[j], std::to_string(i)[0], ' ', files[j], std::to_string(i-2)[0]};
						possibleMoves.push_back(line);
					}
				}
				// Move one space forward
				if (i-1 >= 0 && data[i-1][j]->GetType() == '*') {
					std::string line = {type, files[j], std::to_string(i)[0], ' ', files[j], std::to_string(i-1)[0]};
					possibleMoves.push_back(line);
				}
				// Take left
				if (i-1 >= 0  && j-1>=0 && data[i-1][j-1]->GetColor() == 'B') {
					std::string line = {type, files[j], std::to_string(i)[0], ' ', 'x', files[j-1], std::to_string(i-1)[0]};
					possibleMoves.push_back(line);
				}
				// Take right
				if (i-1 >= 0  && j+1>=0 && data[i-1][j-1]->GetColor() == 'B') {
					std::string line = {type, files[j], std::to_string(i)[0], ' ', 'x', files[j+1], std::to_string(i-1)[0]};
					possibleMoves.push_back(line);
				}

			} else if (color == 'B' && type == 'P' && !whiteToMove) {

				// If it is any other piece of the right color
			} else if ((color == 'W' && whiteToMove) || (color == 'B' && !whiteToMove)) {
				if (type == 'R') {
					bool moveLeft = true;
					bool moveRight = true;
					bool moveUp = true;
					bool moveDown = true;
					for (short k=0; k<4; k++) {
						bool outOfBounds = false;
						for (short l=1; l<8; l++) {
							if ((j+l>7 && k==0) || (j-l<0 && k==1) || (i+l>7 && k==2) || (k-l<0 && k==3)) {
								outOfBounds = true;
								continue;
							}
							bool canMove = false;
							Piece* pieceInQuestion;
							short file = 0;
							short rank = 0;
							if (k==0) {
								pieceInQuestion = data[i][j+l];
								file = j+l;
								rank = 8-i;
							} else if (k==1) {
								pieceInQuestion = data[i][j-l];
								file = j-l;
								rank = 8-i;
							} else if (k==2) {
								pieceInQuestion = data[i+l][j];
								file = j;
								rank = 8-i-l;
							} else {
								pieceInQuestion = data[i-l][j];
								file = j;
								rank = 8-i+l;
								if ((k==0 && moveRight) || (k==1 && moveLeft) || (k==2 && moveDown) || (k==3 && moveUp))
									canMove = true;
								if ((pieceInQuestion.GetType() == '*' || pieceInQuestion.GetColor() != color) && canMove) {
									std::string s({files[j], char(8-i), ' ' ,files[file], char(rank)});
									possibleMoves.push_back(s);
								} else {
									if (k==0)
										moveRight = false;
									else if (k==1)
										moveLeft = false;
									else if (k==2)
										moveDown = false;
									else
										moveUp = false;
								}
							}
						}
					}
				}
			}
		}
	}
	return possibleMoves;
}

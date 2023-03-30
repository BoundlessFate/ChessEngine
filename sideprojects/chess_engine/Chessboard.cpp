#include "Chessboard.h"
char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
Chessboard::Chessboard() {
	data = new Piece*[8];
	data[0] = new Piece[8]
	{Piece('R', 'B'),Piece('N', 'B'),Piece('B', 'B'),Piece('Q', 'B'),Piece('K', 'B'),Piece('B', 'B'),Piece('N', 'B'),Piece('R', 'B')};
	data[1] = new Piece[8]
	{Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B'),Piece('P', 'B')};
	data[2] = new Piece[8]
	{Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E')};
	data[3] = new Piece[8]
	{Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E')};
	data[4] = new Piece[8]
	{Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E')};
	data[5] = new Piece[8]
	{Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E'),Piece('*', 'E')};
	data[6] = new Piece[8]
	{Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W'),Piece('P', 'W')};
	data[7] = new Piece[8]
	{Piece('R', 'W'),Piece('N', 'W'),Piece('B', 'W'),Piece('Q', 'W'),Piece('K', 'W'),Piece('B', 'W'),Piece('N', 'W'),Piece('R', 'W')};
}
Chessboard::Chessboard(Chessboard& a) {
	data = new Piece*[8];
	for (unsigned int i=0; i<8; i++) {
		Piece** oldBoard = a.getBoard();
		data[i] = new Piece[8] {Piece(oldBoard[i][0].GetType(), oldBoard[i][0].GetColor()),
			Piece(oldBoard[i][1].GetType(), oldBoard[i][1].GetColor()),
			Piece(oldBoard[i][2].GetType(), oldBoard[i][2].GetColor()),
			Piece(oldBoard[i][3].GetType(), oldBoard[i][3].GetColor()),
			Piece(oldBoard[i][4].GetType(), oldBoard[i][4].GetColor()),
			Piece(oldBoard[i][5].GetType(), oldBoard[i][5].GetColor()),
			Piece(oldBoard[i][6].GetType(), oldBoard[i][6].GetColor()),
			Piece(oldBoard[i][7].GetType(), oldBoard[i][7].GetColor())
		};
	}
}
Chessboard::~Chessboard() {
	for (short i=0; i<8; i++) {
		delete data[i];
	}
	delete data;
}
std::vector<std::string> Chessboard::CheckValidMoves() {
	std::vector<std::string> possibleMoves;
	for (short i=0; i<8; i++) {
		for (short j=0; j<8; j++) {
			char color = data[i][j].GetColor();
			char type = data[i][j].GetType();
			// If the piece is a pawn (separate check since they can only move in one direction
			if (color == 'W' && type == 'P' && whiteToMove) {

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

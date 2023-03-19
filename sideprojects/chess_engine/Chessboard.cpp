#include "Chessboard.h"
Chessboard::Chessboard(char aMove) {
	data.push_back(Piece('R', 'A', 1, 'W'));
	data.push_back(Piece('N', 'B', 1, 'W'));
	data.push_back(Piece('B', 'C', 1, 'W'));
	data.push_back(Piece('Q', 'D', 1, 'W'));
	data.push_back(Piece('K', 'E', 1, 'W'));
	data.push_back(Piece('B', 'F', 1, 'W'));
	data.push_back(Piece('N', 'G', 1, 'W'));
	data.push_back(Piece('R', 'H', 1, 'W'));
	data.push_back(Piece('P', 'A', 2, 'W'));
	data.push_back(Piece('P', 'B', 2, 'W'));
	data.push_back(Piece('P', 'C', 2, 'W'));
	data.push_back(Piece('P', 'D', 2, 'W'));
	data.push_back(Piece('P', 'E', 2, 'W'));
	data.push_back(Piece('P', 'F', 2, 'W'));
	data.push_back(Piece('P', 'G', 2, 'W'));
	data.push_back(Piece('P', 'H', 2, 'W'));
	data.push_back(Piece('R', 'A', 8, 'B'));
	data.push_back(Piece('N', 'B', 8, 'B'));
	data.push_back(Piece('B', 'C', 8, 'B'));
	data.push_back(Piece('Q', 'D', 8, 'B'));
	data.push_back(Piece('K', 'E', 8, 'B'));
	data.push_back(Piece('B', 'F', 8, 'B'));
	data.push_back(Piece('N', 'G', 8, 'B'));
	data.push_back(Piece('R', 'H', 8, 'B'));
	data.push_back(Piece('P', 'A', 7, 'B'));
	data.push_back(Piece('P', 'B', 7, 'B'));
	data.push_back(Piece('P', 'C', 7, 'B'));
	data.push_back(Piece('P', 'D', 7, 'B'));
	data.push_back(Piece('P', 'E', 7, 'B'));
	data.push_back(Piece('P', 'F', 7, 'B'));
	data.push_back(Piece('P', 'G', 7, 'B'));
	data.push_back(Piece('P', 'H', 7, 'B'));
	if (aMove == 'W')
		whiteToMove = true;
	else
		whiteToMove = false;
}

#include "Chessboard.h"
#include <iostream>
#include <cassert>
std::vector<char> files = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
std::vector<char> promotions = {'B', 'N', 'R', 'Q'};
Chessboard::Chessboard(char a) {
	whiteToMove = true;
	for (unsigned int i=0; i<8; i++) {
		data.push_back(std::vector<Piece*>());
		for (unsigned int j=0; j<8; j++) {
			data[i].push_back(NULL);
		}
	}
	// Test Board 1
	/* data[0][0] = new Piece('*', 'E'); */
	/* data[0][1] = new Piece('R', 'B'); */
	/* data[0][2] = new Piece('*', 'E'); */
	/* data[0][3] = new Piece('*', 'E'); */
	/* data[0][4] = new Piece('*', 'E'); */
	/* data[0][5] = new Piece('*', 'E'); */
	/* data[0][6] = new Piece('*', 'E'); */
	/* data[0][7] = new Piece('Q', 'B'); */
	/* data[1][0] = new Piece('*', 'E'); */
	/* data[1][1] = new Piece('*', 'E'); */
	/* data[1][2] = new Piece('P', 'W'); */
	/* data[1][3] = new Piece('*', 'E'); */
	/* data[1][4] = new Piece('K', 'B'); */
	/* data[1][5] = new Piece('*', 'E'); */
	/* data[1][6] = new Piece('P', 'B'); */
	/* data[1][7] = new Piece('*', 'E'); */
	/* data[2][0] = new Piece('*', 'E'); */
	/* data[2][1] = new Piece('*', 'E'); */
	/* data[2][2] = new Piece('*', 'E'); */
	/* data[2][3] = new Piece('*', 'E'); */
	/* data[2][4] = new Piece('*', 'E'); */
	/* data[2][5] = new Piece('B', 'B'); */
	/* data[2][6] = new Piece('*', 'E'); */
	/* data[2][7] = new Piece('*', 'E'); */
	/* data[3][0] = new Piece('*', 'E'); */
	/* data[3][1] = new Piece('*', 'E'); */
	/* data[3][2] = new Piece('K', 'W'); */
	/* data[3][3] = new Piece('*', 'E'); */
	/* data[3][4] = new Piece('N', 'B'); */
	/* data[3][5] = new Piece('*', 'E'); */
	/* data[3][6] = new Piece('*', 'E'); */
	/* data[3][7] = new Piece('R', 'W'); */
	/* data[4][0] = new Piece('*', 'E'); */
	/* data[4][1] = new Piece('*', 'E'); */
	/* data[4][2] = new Piece('*', 'E'); */
	/* data[4][3] = new Piece('P', 'W'); */
	/* data[4][4] = new Piece('*', 'E'); */
	/* data[4][5] = new Piece('N', 'B'); */
	/* data[4][6] = new Piece('*', 'E'); */
	/* data[4][7] = new Piece('*', 'E'); */
	/* data[5][0] = new Piece('*', 'E'); */
	/* data[5][1] = new Piece('R', 'W'); */
	/* data[5][2] = new Piece('*', 'E'); */
	/* data[5][3] = new Piece('*', 'E'); */
	/* data[5][4] = new Piece('Q', 'W'); */
	/* data[5][5] = new Piece('N', 'W'); */
	/* data[5][6] = new Piece('*', 'E'); */
	/* data[5][7] = new Piece('*', 'E'); */
	/* data[6][0] = new Piece('*', 'E'); */
	/* data[6][1] = new Piece('B', 'W'); */
	/* data[6][2] = new Piece('P', 'W'); */
	/* data[6][3] = new Piece('*', 'E'); */
	/* data[6][4] = new Piece('*', 'E'); */
	/* data[6][5] = new Piece('*', 'E'); */
	/* data[6][6] = new Piece('*', 'E'); */
	/* data[6][7] = new Piece('*', 'E'); */
	/* data[7][0] = new Piece('*', 'E'); */
	/* data[7][1] = new Piece('N', 'W'); */
	/* data[7][2] = new Piece('*', 'E'); */
	/* data[7][3] = new Piece('*', 'E'); */
	/* data[7][4] = new Piece('*', 'E'); */
	/* data[7][5] = new Piece('*', 'E'); */
	/* data[7][6] = new Piece('*', 'E'); */
	/* data[7][7] = new Piece('*', 'E'); */

	/* // Standard Game */
	/* data[0][0] = new Piece('R', 'B'); */
	/* data[0][1] = new Piece('N', 'B'); */
	/* data[0][2] = new Piece('B', 'B'); */
	/* data[0][3] = new Piece('Q', 'B'); */
	/* data[0][4] = new Piece('K', 'B'); */
	/* data[0][5] = new Piece('B', 'B'); */
	/* data[0][6] = new Piece('N', 'B'); */
	/* data[0][7] = new Piece('R', 'B'); */
	/* for (unsigned int i=0; i<8; i++) { */
	/* 	data[1][i] = new Piece('P', 'B'); */
	/* } */
	/* for (unsigned int i=2; i<6; i++) { */
	/* 	for (unsigned int j=0; j<8; j++) { */
	/* 		data[i][j] = new Piece('*', 'E'); */
	/* 	} */
	/* } */
	/* for (unsigned int i=0; i<8; i++) { */
	/* 	data[6][i] = new Piece('P', 'W'); */
	/* } */
	/* data[7][0] = new Piece('R', 'W'); */
	/* data[7][1] = new Piece('N', 'W'); */
	/* data[7][2] = new Piece('B', 'W'); */
	/* data[7][3] = new Piece('Q', 'W'); */
	/* data[7][4] = new Piece('K', 'W'); */
	/* data[7][5] = new Piece('B', 'W'); */
	/* data[7][6] = new Piece('N', 'W'); */
	/* data[7][7] = new Piece('R', 'W'); */

	// Castle Board
	/* data[0][0] = new Piece('R', 'B'); */
	/* data[0][1] = new Piece('N', 'B'); */
	/* data[0][2] = new Piece('B', 'B'); */
	/* data[0][3] = new Piece('Q', 'B'); */
	/* data[0][4] = new Piece('K', 'B'); */
	/* data[0][5] = new Piece('B', 'B'); */
	/* data[0][6] = new Piece('N', 'B'); */
	/* data[0][7] = new Piece('R', 'B'); */
	/* for (unsigned int i=0; i<8; i++) { */
	/* 	data[1][i] = new Piece('P', 'B'); */
	/* } */
	/* for (unsigned int i=2; i<6; i++) { */
	/* 	for (unsigned int j=0; j<8; j++) { */
	/* 		data[i][j] = new Piece('*', 'E'); */
	/* 	} */
	/* } */
	/* for (unsigned int i=0; i<8; i++) { */
	/* 	data[6][i] = new Piece('P', 'W'); */
	/* } */
	/* data[7][0] = new Piece('R', 'W'); */
	/* data[7][1] = new Piece('*', 'E'); */
	/* data[7][2] = new Piece('*', 'E'); */
	/* data[7][3] = new Piece('*', 'E'); */
	/* data[7][4] = new Piece('K', 'W'); */
	/* data[7][5] = new Piece('*', 'E'); */
	/* data[7][6] = new Piece('*', 'E'); */
	/* data[7][7] = new Piece('R', 'W'); */

	// Castle Through Check Board
	data[0][0] = new Piece('R', 'B');
	data[0][1] = new Piece('N', 'B');
	data[0][2] = new Piece('B', 'B');
	data[0][3] = new Piece('Q', 'B');
	data[0][4] = new Piece('K', 'B');
	data[0][5] = new Piece('B', 'B');
	data[0][6] = new Piece('N', 'B');
	data[0][7] = new Piece('R', 'B');
	for (unsigned int i=1; i<7; i++) {
		for (unsigned int j=0; j<8; j++) {
			data[i][j] = new Piece('*', 'E');
		}
	}
	data[7][0] = new Piece('R', 'W');
	data[7][1] = new Piece('*', 'E');
	data[7][2] = new Piece('*', 'E');
	data[7][3] = new Piece('*', 'E');
	data[7][4] = new Piece('K', 'W');
	data[7][5] = new Piece('*', 'E');
	data[7][6] = new Piece('*', 'E');
	data[7][7] = new Piece('R', 'W');


	// Checkmate test
	/* for (unsigned int i=0; i<6; i++) { */
	/* 	for (unsigned int j=0; j<8; j++) { */
	/* 		data[i][j] = new Piece('*', 'E'); */
	/* 	} */
	/* } */
	/* data[6][0] = new Piece('R', 'B'); */
	/* data[6][1] = new Piece('*', 'E'); */
	/* data[6][2] = new Piece('*', 'E'); */
	/* data[6][3] = new Piece('*', 'E'); */
	/* data[6][4] = new Piece('*', 'E'); */
	/* data[6][5] = new Piece('*', 'E'); */
	/* data[6][6] = new Piece('*', 'E'); */
	/* data[6][7] = new Piece('*', 'E'); */
	/* data[7][0] = new Piece('R', 'B'); */
	/* data[7][1] = new Piece('*', 'E'); */
	/* data[7][2] = new Piece('*', 'E'); */
	/* data[7][3] = new Piece('*', 'E'); */
	/* data[7][4] = new Piece('K', 'W'); */
	/* data[7][5] = new Piece('*', 'E'); */
	/* data[7][6] = new Piece('*', 'E'); */
	/* data[7][7] = new Piece('K', 'B'); */

}
Chessboard::Chessboard(Chessboard& a) {
	for (unsigned int i=0; i<8; i++) {
		data.push_back(std::vector<Piece*>());
		for (unsigned int j=0; j<8; j++) {
			data[i].push_back(NULL);
		}
	}
	std::vector<std::vector<Piece*>> oldBoard = a.getBoard();
	for (unsigned int i=0; i<8; i++) {
		for (unsigned int j=0; j<8; j++) {
			data[i][j] = new Piece(oldBoard[i][j]->GetType(), oldBoard[i][j]->GetColor());
		}
	}
	assert(data.size() == 8);
	assert(data[0].size() == 8);
}
Chessboard::~Chessboard() {
	for (unsigned int i=0; i<8; i++) {
		for (unsigned int j=0; j<8; j++) {
			delete data[i][j];
		}
	}
}

std::vector<std::string> Chessboard::PawnMoves(std::string lastMove, short i, short j, char color, char type) {
	short movementMultiplier = 1;
	if (color == 'B')
		movementMultiplier = -1;
	std::vector<std::string> possibleMoves;
	if ((i == 6 && color == 'W') || (i==1 && color == 'B')) {
		// Allow move two spaces if the pawn is on the starting rank and is unobstructed
		if ((color == 'W' && data[5][j]->GetType() == '*' && data[4][j]->GetType() == '*') ||
				(color == 'B' && data[2][j]->GetType() == '*' && data[3][j]->GetType() == '*')) {
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[j], std::to_string(8-i+(2*movementMultiplier))[0]});
		}
	}
	// Check for moves one space forward
	if (data[i-movementMultiplier][j]->GetType() == '*') {
		if ((i != 1 && color == 'W') || (i != 6 && color == 'B'))
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[j], std::to_string(8-i+movementMultiplier)[0]});
		else {
			// Checking for promotions when moving up
			for (short k=0; k<3; k++)
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[j], 
						std::to_string(8-i+movementMultiplier)[0], '=', promotions[k]});
		}
	}
	// Taking on the sides
	for (short k=-1; k<2; k+=2) {
		if (0<=(j+k) && (j+k)<=7 && ((data[i-movementMultiplier][j+k]->GetColor() == 'B' && color == 'W') ||
					(data[i-movementMultiplier][j+k]->GetColor() == 'W' && color == 'B'))) {
			// If you dont need to promote
			if (0 < i-movementMultiplier && i-movementMultiplier < 7)
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[j+k], std::to_string(8-i+movementMultiplier)[0]});
			// If you can promote
			else {	
				for (short l=0; l<3; l++)
					possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[j+k], std::to_string(8-i+movementMultiplier)[0], '=', promotions[l]});
			}
		}
		// En passant checks
		if (((color == 'W' && i==3) || (color == 'B' && i==4)) && j+k>=0 && j+k<=7) {
			std::string checkEnPassant = {'P', files[j+k], '7', ' ', files[j+k], '5'};
			if (color == 'B')
				checkEnPassant = {'P', files[j+k], '2', ' ', files[j+k], '4'};
			if (lastMove == checkEnPassant)
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[j+k], std::to_string(8-i+movementMultiplier)[0]});
		}
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::RookMoves(short i, short j, char color, char type) {
	std::vector<std::string> possibleMoves;
	// 4 directions
	for (short k=0; k<4; k++) {
		// Movement to the edge of the board
		for (short l=1; l<8; l++) {
			// Go to next direction if out of bounds
			if ((j+l>7 && k==0) || (j-l<0 && k==1) || (i+l>7 && k==2) || (i-l<0 && k==3)) {
				break;
			}
			Piece* pieceInQuestion;
			short file = j;
			short rank = i;
			if (k==0) {
				pieceInQuestion = data[i][j+l];
				file+=l;
			} else if (k==1) {
				pieceInQuestion = data[i][j-l];
				file-=l;
			} else if (k==2) {
				pieceInQuestion = data[i+l][j];
				rank+=l;
			} else {
				pieceInQuestion = data[i-l][j];
				rank-=l;
			}
			// If the piece at the space is the same color as the current rook
			if (pieceInQuestion->GetColor() == color)
				break;
			// If the space is an opposing piece
			if ((pieceInQuestion->GetColor() == 'W' && !whiteToMove) || (pieceInQuestion->GetColor() == 'B' && whiteToMove)) {
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[file], std::to_string(8-rank)[0]});
				break;
			}
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[file], std::to_string(8-rank)[0]});
		}
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::BishopMoves(short i, short j, char color, char type) {					
	std::vector<std::string> possibleMoves;
	// 4 directions
	for (short k=0; k<4; k++) {
		// Movement to the edge of the board
		for (short l=1; l<8; l++) {
			if (((j+l>7 || i-l<0) && k==0) || ((j-l<0||i-l<0) && k==1) || ((i+l>7||j+l>7) && k==2) || ((i+l>7||j-l<0) && k==3)) {
				break;
			}
			Piece* pieceInQuestion;
			short file = j;
			short rank = i;
			if (k==0) {
				pieceInQuestion = data[i-l][j+l];
				rank-=l;
				file+=l;
			} else if (k==1) {
				pieceInQuestion = data[i-l][j-l];
				rank-=l;
				file-=l;
			} else if (k==2) {
				pieceInQuestion = data[i+l][j+l];
				rank+=l;
				file+=l;
			} else {
				pieceInQuestion = data[i+l][j-l];
				rank+=l;
				file-=l;
			}
			// If the piece at the space is the same color as the current bishop
			if (pieceInQuestion->GetColor() == color)
				break;
			// If the space is an opposing piece
			if ((pieceInQuestion->GetColor() == 'W' && !whiteToMove) || (pieceInQuestion->GetColor() == 'B' && whiteToMove)) {
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[file], std::to_string(8-rank)[0]});
				break;
			}
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[file], std::to_string(8-rank)[0]});
		}
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::QueenMoves(short i, short j, char color, char type) {					
	std::vector<std::string> possibleMoves;
	// 8 directions
	for (short k=0; k<8; k++) {
		// Movement to the edge of the board
		for (short l=1; l<8; l++) {
			if ((j+l>7 && k==0) || (j-l<0 && k==1) || (i+l>7 && k==2) || (i-l<0 && k==3) || 
					((j+l>7 || i-l<0) && k==4) || ((j-l<0||i-l<0) && k==5) || ((i+l>7||j+l>7) && k==6) || ((i+l>7||j-l<0) && k==7)) {
				break;
			}
			Piece* pieceInQuestion;
			short file = j;
			short rank = i;
			if (k==0) {
				pieceInQuestion = data[i][j+l];
				file+=l;
			} else if (k==1) {
				pieceInQuestion = data[i][j-l];
				file-=l;
			} else if (k==2) {
				pieceInQuestion = data[i+l][j];
				rank+=l;
			} else if (k==3) {
				pieceInQuestion = data[i-l][j];
				rank-=l;
			} else if (k==4) {
				pieceInQuestion = data[i-l][j+l];
				rank-=l;
				file+=l;
			} else if (k==5) {
				pieceInQuestion = data[i-l][j-l];
				rank-=l;
				file-=l;
			} else if (k==6) {
				pieceInQuestion = data[i+l][j+l];
				rank+=l;
				file+=l;
			} else {
				pieceInQuestion = data[i+l][j-l];
				rank+=l;
				file-=l;
			}
			// If the piece at the space is the same color as the current rook
			if (pieceInQuestion->GetColor() == color)
				break;
			// If the space is an opposing piece
			if ((pieceInQuestion->GetColor() == 'W' && !whiteToMove) || (pieceInQuestion->GetColor() == 'B' && whiteToMove)) {
				possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[file], std::to_string(8-rank)[0]});
				break;
			}
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[file], std::to_string(8-rank)[0]});
		}
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::KingMoves(short i, short j, char color, char type) {					
	std::vector<std::string> possibleMoves;
	// 8 directions
	for (short k=0; k<8; k++) {
		if ((j+1>7 && k==0) || (j-1<0 && k==1) || (i+1>7 && k==2) || (i-1<0 && k==3) || 
				((j+1>7 || i-1<0) && k==4) || ((j-1<0||i-1<0) && k==5) || ((i+1>7||j+1>7) && k==6) || ((i+1>7||j-1<0) && k==7)) {
			continue;
		}
		Piece* pieceInQuestion;
		short file = j;
		short rank = i;
		if (k==0) {
			pieceInQuestion = data[i][j+1];
			file+=1;
		} else if (k==1) {
			pieceInQuestion = data[i][j-1];
			file-=1;
		} else if (k==2) {
			pieceInQuestion = data[i+1][j];
			rank+=1;
		} else if (k==3) {
			pieceInQuestion = data[i-1][j];
			rank-=1;
		} else if (k==4) {
			pieceInQuestion = data[i-1][j+1];
			rank-=1;
			file+=1;
		} else if (k==5) {
			pieceInQuestion = data[i-1][j-1];
			rank-=1;
			file-=1;
		} else if (k==6) {
			pieceInQuestion = data[i+1][j+1];
			rank+=1;
			file+=1;
		} else {
			pieceInQuestion = data[i+1][j-1];
			rank+=1;
			file-=1;
		}
		// If the piece at the space is the same color as the current rook
		if (pieceInQuestion->GetColor() == color)
			continue;
		// If the space is an opposing piece
		if ((pieceInQuestion->GetColor() == 'W' && !whiteToMove) || (pieceInQuestion->GetColor() == 'B' && whiteToMove)) {
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[file], std::to_string(8-rank)[0]});
			continue;
		}
		possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[file], std::to_string(8-rank)[0]});
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::KnightMoves(short i, short j, char color, char type) {	
	std::vector<std::string> possibleMoves;// 8 directions
	for (short k=0; k<8; k++) {
		if (((j+1>7||i-2<0) && k==0) || ((j-1<0||i-2<0) && k==1) || ((j-2<0||i-1<0) && k==2) || ((j-2<0||i+1>7) && k==3)
				|| ((j-1<0||i+2>7) && k==4) || ((j+1>7||i+2>7) && k==5) || ((j+2>7||i+1>7) && k==6) || ((j+2>7||i-1<0) && k==7)) {
			continue;
		}
		Piece* pieceInQuestion;
		short file = j;
		short rank = i;
		if (k==0) {
			pieceInQuestion = data[i-2][j+1];
			file+=1;
			rank-=2;
		} else if (k==1) {
			pieceInQuestion = data[i-2][j-1];
			file-=1;
			rank-=2;
		} else if (k==2) {
			pieceInQuestion = data[i-1][j-2];
			rank-=1;
			file-=2;
		} else if (k==3) {
			pieceInQuestion = data[i+1][j-2];
			rank+=1;
			file-=2;
		} else if (k==4) {
			pieceInQuestion = data[i+2][j-1];
			rank+=2;
			file-=1;
		} else if (k==5) {
			pieceInQuestion = data[i+2][j+1];
			rank+=2;
			file+=1;
		} else if (k==6) {
			pieceInQuestion = data[i+1][j+2];
			rank+=1;
			file+=2;
		} else {
			pieceInQuestion = data[i-1][j+2];
			rank-=1;
			file+=2;
		}
		// If the piece at the space is the same color as the current rook
		if (pieceInQuestion->GetColor() == color)
			continue;
		// If the space is an opposing piece
		if ((pieceInQuestion->GetColor() == 'W' && !whiteToMove) || (pieceInQuestion->GetColor() == 'B' && whiteToMove)) {
			possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', 'x', files[file], std::to_string(8-rank)[0]});
			continue;
		}
		possibleMoves.push_back({type, files[j], std::to_string(8-i)[0], ' ', files[file], std::to_string(8-rank)[0]});
	}

	return possibleMoves;
}

std::vector<std::string> Chessboard::CastleMoves() {	
	std::vector<std::string> possibleMoves;
	if (whiteToMove) {
		if (data[7][0]->GetType() == 'R' && data[7][1]->GetType() == '*' && data[7][2]->GetType() == '*'
				&& data[7][3]->GetType() == '*' && data[7][4]->GetType() == 'K'
				&& !data[7][0]->HasMoved() && !data[7][4]->HasMoved()) {
			possibleMoves.push_back("O-O-O");
		}
		if (data[7][7]->GetType() == 'R' && data[7][6]->GetType() == '*' && data[7][5]->GetType() == '*'
				&& data[7][4]->GetType() == 'K'
				&& !data[7][7]->HasMoved() && !data[7][4]->HasMoved()) {
			possibleMoves.push_back("O-O");
		}
	} else {
		if (data[0][0]->GetType() == 'R' && data[0][1]->GetType() == '*' && data[0][2]->GetType() == '*'
				&& data[0][3]->GetType() == '*' && data[0][4]->GetType() == 'K'
				&& !data[0][0]->HasMoved() && !data[0][4]->HasMoved()) {
			possibleMoves.push_back("O-O-O");
		}
		if (data[0][7]->GetType() == 'R' && data[0][6]->GetType() == '*' && data[0][5]->GetType() == '*'
				&& data[0][4]->GetType() == 'K'
				&& !data[0][7]->HasMoved() && !data[0][4]->HasMoved()) {
			possibleMoves.push_back("O-O");
		}
	}
	return possibleMoves;
}

std::vector<std::string> Chessboard::CheckValidMoves(std::string lastMove) {
	std::vector<std::string> possibleMoves;
	std::vector<std::string> tempMoves;
	for (short i=0; i<8; i++) {
		for (short j=0; j<8; j++) {
			char color = data[i][j]->GetColor();
			char type = data[i][j]->GetType();
			if ((whiteToMove && color == 'W') || (!whiteToMove && color == 'B')) {
				// Code for Pawn
				if (type == 'P') {
					tempMoves = PawnMoves(lastMove, i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
					// Code for Rook
				} else if (type == 'R') {
					tempMoves = RookMoves(i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
					// Code for Bishop
				} else if (type == 'B') {
					tempMoves = BishopMoves(i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
					// Code For Queen
				} else if (type == 'Q') {
					tempMoves = QueenMoves(i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
					// Code For King
				} else if (type == 'K') {
					tempMoves = KingMoves(i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
					// Code For Knight
				} else if (type == 'N') {
					tempMoves = KnightMoves(i, j, color, type);
					for (unsigned int k=0; k<tempMoves.size(); k++)
						possibleMoves.push_back(tempMoves[k]);
				}
			}
		}
	}
	tempMoves = CastleMoves();
	for (unsigned int k=0; k<tempMoves.size(); k++)
		possibleMoves.push_back(tempMoves[k]);
	return possibleMoves;
}

void Chessboard::ProcessMove(std::string& move) {
	int castleNum = 7;
	if (!whiteToMove)
		castleNum = 0;
	if (move == "O-O") {
		Piece* king = data[castleNum][4];
		Piece* rook = data[castleNum][7];
		data[castleNum][4] = new Piece('*','E');
		data[castleNum][7] = new Piece('*', 'E');
		Piece* emptyKingSquare = data[castleNum][6];
		Piece* emptyRookSquare = data[castleNum][5];
		data[castleNum][6] = king;
		data[castleNum][5] = rook;
		delete emptyKingSquare;
		delete emptyRookSquare;
		king->Move();
		rook->Move();
		return;
	} else if (move == "O-O-O") {
		Piece* king = data[castleNum][4];
		Piece* rook = data[castleNum][0];
		data[castleNum][4] = new Piece('*','E');
		data[castleNum][0] = new Piece('*', 'E');
		Piece* emptyKingSquare = data[castleNum][2];
		Piece* emptyRookSquare = data[castleNum][3];
		data[castleNum][2] = king;
		data[castleNum][3] = rook;
		delete emptyKingSquare;
		delete emptyRookSquare;
		king->Move();
		rook->Move();
		return;
	} else if (move == "O-O-O") {
		Piece* king = data[castleNum][4];
		Piece* rook = data[castleNum][0];
		data[castleNum][4] = new Piece('*','E');
		data[castleNum][0] = new Piece('*', 'E');
		Piece* emptyKingSquare = data[castleNum][2];
		Piece* emptyRookSquare = data[castleNum][3];
		data[castleNum][2] = king;
		data[castleNum][3] = rook;
		delete emptyKingSquare;
		delete emptyRookSquare;
		return;
	}

	int originalFile = -1;
	int originalRank = move[2] - '0';
	for(unsigned int i=0; i<files.size(); i++) {
		if (files[i] == move[1]) {
			originalFile = i;
			break;
		}
	}
	Piece* originalPiece = data[8-originalRank][originalFile];
	// Replace original spot with empty square
	data[8-originalRank][originalFile] = new Piece('*','E');
	int finalFile = -1;
	// If piece is not promoting
	if (move[move.size()-2] != '=') {
		int finalRank = move[move.size()-1] - '0';
		for(unsigned int i=0; i<files.size(); i++) {
			if (files[i] == move[move.size()-2]) {
				finalFile = i;
				break;
			}
		}
		// Replace new spot and delete old piece
		Piece* oldPiece = data[8-finalRank][finalFile];
		data[8-finalRank][finalFile] = originalPiece;
		delete oldPiece;
		originalPiece->Move();
		// If you need to promote the piece
	} else {
		Piece* newPiece = new Piece(move[move.size()-1], originalPiece->GetColor());
		data[8-originalRank][originalFile] = new Piece('*','E');
		delete originalPiece;
		int finalRank = move[move.size()-3] - '0';
		for(unsigned int i=0; i<files.size(); i++) {
			if (files[i] == move[move.size()-4]) {
				finalFile = i;
				break;
			}
		}
		// Replace new spot and delete old piece
		Piece* oldPiece = data[8-finalRank][finalFile];
		data[8-finalRank][finalFile] = newPiece;
		delete oldPiece;
		newPiece->Move();
	}
	return;
}

Piece* Chessboard::GetPiece(char file, int rank) {
	int fileVar = -1;
	for (unsigned int i=0; i<files.size(); i++) {
		if (files[i] == file) {
			fileVar = i;
			break;
		}
	}
	return data[rank][fileVar];
}
void Chessboard::DisplayBoard() {
	for (unsigned int i=0; i<8; i++) {
		// Color Line
		for (unsigned int j=0; j<8; j++) {
			if (data[i][j]->GetColor() == 'E')
				std::cout << "--    ";
			else
				std::cout << data[i][j]->GetColor() << '*' << "    ";
		}
		std::cout << std::endl;
		// Type Line
		for (unsigned int j=0; j<8; j++) {
			if (data[i][j]->GetType() == '*')
				std::cout << "--    ";
			else
				std::cout << '*' << data[i][j]->GetType() << "    ";
		}
		std::cout << std::endl << std::endl;
	}
	return;
}

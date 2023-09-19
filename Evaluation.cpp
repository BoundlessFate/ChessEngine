#include "Chessboard.cpp"
float EvaluatePosition(Chessboard* board) {
	float boardEval = 0;
	for (short i=0; i<8; i++) {
		for (short j=0; j<8; j++) {
			Piece* currentPiece = board->GetPiece(files[i], j);
			float currentPieceEval = 0;
			if (currentPiece->GetType() == 'P')
				currentPieceEval = 1;
			else if (currentPiece->GetType() == 'N')
				currentPieceEval = 3.25;
			else if (currentPiece->GetType() == 'B')
				currentPieceEval = 3.25;
			else if (currentPiece->GetType() == 'R')
				currentPieceEval = 5;
			else if (currentPiece->GetType() == 'Q')
				currentPieceEval = 10.5;
			// Bot really shouldnt need the king code here, as a path where the checkmate 
			// is found will just be set to 99999 anyway
			else if (currentPiece->GetType() == 'K')
				currentPieceEval = 99999;
			if (currentPiece->GetColor() == 'B')
				currentPieceEval *= -1;
			boardEval += currentPieceEval;
		}
	}
	return boardEval;
}

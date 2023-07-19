#include "Chessboard.cpp"
float EvaluatePosition(Chessboard& board) {
	float boardEval = 0;
	for (short i=0; i<8; i++) {
		for (short j=0; j<8; j++) {
			Piece* currentPiece = board.GetPiece(files[i], j);
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

std::string FindBestMove(Chessboard& board, std::vector<std::string>& allMoves) {
	assert(allMoves.size() != 0);
	std::vector<std::string> allBestMoves;
	// Set bestEval to the worst value possible for the current color
	float bestEval = 0;
	if (board.GetMove())
		bestEval = -99999;
	else
		bestEval = 99999;
	// Check the board evaluation for each move and determine the best one
	for (unsigned int i=0; i<allMoves.size(); i++) {
		Chessboard newBoard(board);
		newBoard.ProcessMove(allMoves[i]);
		float currentMoveEval = EvaluatePosition(newBoard);
		// If the current move is the best move
		if ((newBoard.GetMove() && currentMoveEval > bestEval) ||
				(!newBoard.GetMove() && currentMoveEval < bestEval)) {
			bestEval = currentMoveEval;
			allBestMoves.clear();
			allBestMoves.push_back(allMoves[i]);
		} else if (currentMoveEval == bestEval) {
			// Eval stays the same so no need to change
			allBestMoves.push_back(allMoves[i]);
		}
	}
	return allBestMoves[rand() % allBestMoves.size()];
}

#include "Node.cpp"
#include <stdlib.h>
Node* GenerateTree(Chessboard& board, std::string& lastMove, unsigned int depth) {
	/* std::cout << "Generating Tree..." << std::endl << std::flush; */
	// Create the root node (current board)
	Node* rootNode = new Node(board, lastMove);
	// Increase depth of the tree a given number of times
	for (unsigned int i=0; i<depth; i++) {
 		rootNode->IncreaseDepth();
	}
	/* std::cout << "Tree Generated..." << std::endl << std::flush; */
	/* std::cout << "Tree Size Is: " << rootNode->TotalNodeCount() << std::endl << std::flush; */
	return rootNode;
}


std::string FindBestMove(Chessboard& board, std::vector<std::string>& allMoves, std::string& lastMove, char* depth) {
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
		Node* rootNode = GenerateTree(newBoard, lastMove, std::atoi(depth));
		rootNode->CalculateEval();
		float currentMoveEval = rootNode->GetEval();
		rootNode->DeleteTree();
		if ((newBoard.GetMove() && currentMoveEval > bestEval) ||
				(!newBoard.GetMove() && currentMoveEval < bestEval)) {
			bestEval = currentMoveEval;
			allBestMoves.clear();
			allBestMoves.push_back(allMoves[i]);
		} else if (currentMoveEval == bestEval) {
			// Eval stays the same so no need to change
			allBestMoves.push_back(allMoves[i]);
		}
		std::cout << allMoves[i] << ": " << currentMoveEval << std::endl << std::flush;
	}
	return allBestMoves[rand() % allBestMoves.size()];
}

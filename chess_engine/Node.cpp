#include "Node.h"
Node::Node(Chessboard& boardIn, std::string& move) {
	eval = 0;
	currentBoard = new Chessboard(boardIn);
	currentMove = move;
	mate = 0;
	return;
}
void Node::DeleteTree() {
	for (unsigned int i=0; i<childNodes.size(); i++) {
		childNodes[i]->DeleteTree();
	}
	delete currentBoard;
}
void Node::SetEval(float evalIn) {
	eval = evalIn;
	evalSet = true;
}
void Node::CreateChildren() {
	Chessboard newBoard(*currentBoard);
	newBoard.FlipMove();
	std::vector<std::string> allMoves = newBoard.CheckValidMoves(currentMove);
	allMoves = PinsAndChecks(allMoves, newBoard);
	if (allMoves.size() == 0) {
		if (CheckmateCheck(newBoard, currentMove)) {
			newBoard.FlipMove();
			if (newBoard.GetMove())
				mate = 1;
			else
				mate = 2;
			return;
		}
		mate = 3;
		return;
	}
	for (unsigned int i=0; i<allMoves.size(); i++) {
		Chessboard* childBoard = new Chessboard(newBoard);
		childBoard->ProcessMove(allMoves[i]);
		Node* newNode = new Node(*childBoard, allMoves[i]);
		childNodes.push_back(newNode);
	}
	return;
}
void Node::IncreaseDepth() {
	for (unsigned int i=0; i<childNodes.size(); i++)
		childNodes[i]->IncreaseDepth();
	if (childNodes.size() == 0) {
		CreateChildren();
		return;
	}
	return;
}
int Node::TotalNodeCount() {
	/* currentBoard->DisplayBoard(); */
	int counter = 1;
	for (unsigned int i=0; i<childNodes.size(); i++) {
		counter += childNodes[i]->TotalNodeCount();
	}
	return counter;
}

void Node::CalculateEval() {
	if (mate != 0) {
		if (mate == 1) {
			eval = -999999;
		} else if (mate == 2) {
			eval = 999999;
		} else {
			eval = 0;
		}
		evalSet = true;
		return;
	}
	// Go down to all children
	for (unsigned int i=0; i<childNodes.size(); i++) {
		childNodes[i]->CalculateEval();
	}
	// If its a leaf node, calculate its eval
	if (childNodes.size() == 0) {
		eval = EvaluatePosition(currentBoard);
		return;
	}
	// Calculate non leaf node eval
	if (currentBoard->GetMove()) {
		float min = 999999;
		for (unsigned int i=0; i<childNodes.size(); i++) {
			if (childNodes[i]->GetEval() < min)
				min = childNodes[i]->GetEval();
		}
		eval = min;
	} else {
		float max = -999999;
		for (unsigned int i=0; i<childNodes.size(); i++) {
			if (childNodes[i]->GetEval() > max)
				max = childNodes[i]->GetEval();
		}
		eval = max;
	}
	evalSet = true;
	return;
}

#include "Evaluation.cpp"
class Node {
public:
	// Constructor
	Node(Chessboard& boardIn, std::string& move);
	float GetEval() {return eval;}
	void CreateChildren();
	void SetEval(float evalIn);
	std::vector<Node*> GetChildren() {return childNodes;}
	void IncreaseDepth();
	void CalculateEval();
	bool EvalBeenSet() {return evalSet;}
	int TotalNodeCount();
	void DeleteTree();
private:
	Chessboard* currentBoard;
	float eval;
	std::vector<Node*> childNodes;
	bool evalSet;
	int mate;
	std::string currentMove;
};

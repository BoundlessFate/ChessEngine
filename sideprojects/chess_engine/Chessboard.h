#include <vector>
#include "Piece.cpp"
#include <string>
class Chessboard {
public:
	// Constructor
	Chessboard();
	Chessboard(Chessboard& a);
	~Chessboard();
	// Public Functions
	bool GetMove() {return whiteToMove;}
	Piece GetPiece(char rank, int file);
	std::vector<std::string> CheckValidMoves();
	float EvaluatePosition();
	void FlipMove() {whiteToMove = !whiteToMove;}
	std::vector<std::vector<Piece*>> getBoard() {return data;}
private:
	std::vector<std::vector<Piece*>> data;
	bool whiteToMove;
};

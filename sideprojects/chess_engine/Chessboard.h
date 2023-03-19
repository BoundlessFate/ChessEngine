#include <vector>
#include "Piece.cpp"
class Chessboard {
public:
	// Constructor
	Chessboard(char aMove);
	// Public Functions
	bool GetMove() {return whiteToMove;}
	Piece GetPiece(char rank, int file);
	std::vector<std::pair<Piece, std::pair<char, int>>> CheckValidMoves();
	int EvaluatePosition();
	void FlipMove() {whiteToMove = !whiteToMove;}
private:
	std::vector<Piece> data;
	bool whiteToMove;
};

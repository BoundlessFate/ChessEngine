#include <vector>
#include "Piece.cpp"
#include <string>
class Chessboard {
public:
	// Constructor
	Chessboard(char a);
	Chessboard(Chessboard& a);
	~Chessboard();
	// Public Functions
	bool GetMove() {return whiteToMove;}
	Piece* GetPiece(char file, int rank);
	std::vector<std::string> CheckValidMoves(std::string lastMove);
	float EvaluatePosition();
	void FlipMove() {whiteToMove = !whiteToMove;}
	std::vector<std::vector<Piece*>> GetBoard() {return data;}
	void ProcessMove(std::string& move);
	void DisplayBoard();
private:
	std::vector<std::string> PawnMoves(std::string lastMove, short i, short j, char color, char type);
	std::vector<std::string> RookMoves(short i, short j, char color, char type);
	std::vector<std::string> BishopMoves(short i, short j, char color, char type);
	std::vector<std::string> QueenMoves(short i, short j, char color, char type);
	std::vector<std::string> KingMoves(short i, short j, char color, char type);
	std::vector<std::string> KnightMoves(short i, short j, char color, char type);
	std::vector<std::string> CastleMoves();
	std::vector<std::vector<Piece*>> data;
	bool whiteToMove;
};

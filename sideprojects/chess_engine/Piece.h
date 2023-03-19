class Piece {
public:
	// Constructor
	Piece(char aType, char aRank, int aFile, char aColor);
	char GetType() {return type;}
	char GetFile() {return file;}
	int GetRank() {return rank;}
private:
	char type;
	char file;
	int rank;
	char color;
};

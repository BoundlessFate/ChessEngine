class Piece {
public:
	// Constructor
	Piece(char aType, char aColor);
	char GetType() {return type;}
	char GetColor() {return color;}
private:
	char type;
	char color;
};

class Piece {
public:
	// Constructor
	Piece(char aType, char aColor);
	char GetType() {return type;}
	char GetColor() {return color;}
	bool HasMoved() {return moved;}
	void Move() {moved = true;}
private:
	char type;
	char color;
	bool moved;
};

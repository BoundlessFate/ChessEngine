// Include string for current move
#include <string>
// Fighter class
class Fighter {
public:
	// Constructor
	Fighter(std::string aName, int aJabTime, int aFtiltTime, int aUtiltTime,
			int aDtiltTime, int aFsmashTime, int aUsmashTime, int aDsmashTime);
	// Getter functions
	std::string getName() const {return name;}
	int getJabTime() const {return jabTime;}
	int getFtiltTime() const {return ftiltTime;}
	int getUtiltTime() const {return utiltTime;}
	int getDtiltTime() const {return dtiltTime;}
	int getFsmashTime() const {return fsmashTime;}
	int getUsmashTime() const {return usmashTime;}
	int getDsmashTime() const {return dsmashTime;}
	int GetMoveTime() const;
	std::string getMove() const {return move;}
	// Setter functions
	void setMove(std::string aMove) {move = aMove;}
private:
	// Private variables for data
	std::string name;
	std::string move;
	int jabTime;
	int ftiltTime;
	int utiltTime;
	int dtiltTime;
	int fsmashTime;
	int usmashTime;
	int dsmashTime;
};
// < and > overloads for sorting with sets
bool operator< (const Fighter& a, const Fighter& b);
bool operator> (const Fighter& a, const Fighter& b);

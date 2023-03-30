#include <string>
class Fighter {
public:
	Fighter(std::string aName, int aJabTime, int aFtiltTime, int aUtiltTime, int aDtiltTime, int aFsmashTime, int aUsmashTime, int aDsmashTime);
	std::string getName() const {return name;}
	int getJabTime() const {return jabTime;}
	int getFtiltTime() const {return ftiltTime;}
	int getUtiltTime() const {return utiltTime;}
	int getDtiltTime() const {return dtiltTime;}
	int getFsmashTime() const {return fsmashTime;}
	int getUsmashTime() const {return usmashTime;}
	int getDsmashTime() const {return dsmashTime;}
private:
	std::string name;
	int jabTime;
	int ftiltTime;
	int utiltTime;
	int dtiltTime;
	int fsmashTime;
	int usmashTime;
	int dsmashTime;
};

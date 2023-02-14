#include <string>
#include <list>
#include <iostream>
class Item {
public:
	Item(const std::string& aID, unsigned int aStock, const std::string& aName);
	const std::string& getID() const {return ID;}
	unsigned int getStock() const {return stock;}
	const std::string& getName() const {return name;}
	std::list<std::string> getWaitlistID() {return waitlistID;}
	std::list<unsigned int> getWaitlistNum() {return waitlistNum;}
	void rentTool(unsigned int aNum) {stock -= aNum;}
	void returnTool(unsigned int aNum) {stock += aNum;}
	void addToWaitlist(const std::string& aID, unsigned int num);
	std::list<std::string> removeFromWaitlist();
private:
	std::string ID;
	unsigned int stock;
	std::string name;
	std::list<std::string> waitlistID;
	std::list<unsigned int> waitlistNum;
};

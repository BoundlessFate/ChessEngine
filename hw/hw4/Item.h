// string is for std::strings
// list is for std::list
// iostream is for std::cerr
#include <string>
#include <list>
#include <iostream>
// Item Class
class Item {
public:
	// Item constructor
	Item(const std::string& aID, unsigned int aStock, const std::string& aName);
	// Returns the id
	const std::string& getID() const {return ID;}
	// Returns the stock
	unsigned int getStock() const {return stock;}
	// Returns the Name
	const std::string& getName() const {return name;}
	// rents the tool and adjusts values
	void rentTool(unsigned int aNum) {stock -= aNum;}
	// Returns the tool and adjusts values
	void returnTool(unsigned int aNum) {stock += aNum;}
	// Adds an id and number to the waitlist
	void addToWaitlist(const std::string& aID, unsigned int num);
	// Removes an id and its number from the waitlist
	std::list<std::string> removeFromWaitlist();
	// Add an id and its number to the rentingList
	void addRentingList(const std::string& aID, unsigned int aNum);
	// Subtracts aNum from the ids index in rentingList
	void subtractRentingList(const std::string& aID, unsigned int aNum);
	// returns rentingList
	std::list<std::string> getRentingList() const {return rentingList;}
	// Returns the waitlistID
	std::list<std::string> getWaitlistID() const {return waitlistID;}
	// Returns the waitlistNum
	std::list<unsigned int> getWaitlistNum() const {return waitlistNum;}
private:
	// The Item ID
	std::string ID;
	// The Item Stock
	unsigned int stock;
	// The item name
	std::string name;
	// The item waitlist and values people are waiting for
	std::list<std::string> waitlistID;
	// The values of the waitlist
	std::list<unsigned int> waitlistNum;
	// The items list of current renters
	std::list<std::string> rentingList;
};

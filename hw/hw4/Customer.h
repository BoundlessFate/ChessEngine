// Includes string for std::strings and list for std::lists
#include <string>
#include <list>
class Customer {
public:
	// Constructor for the customer object
	Customer(const std::string& aCustomerID, const std::string& aCustomerName);
	// Returns customer id
	const std::string& getCustomerID() const {return customerID;}
	// Returns customer name
	const std::string& getCustomerName() const {return customerName;}
	// Returns the rented list
	const std::list<std::string> getRentedList() const {return rentedList;}
	// Rents the rented list num
	const std::list<unsigned int> getRentedListNum() const {return rentedListNum;}
	// Rents the given item and places it in rentedList
	void rentItem(const std::string& aItemID, unsigned int aNum);
	// Returns an item and takes it out of the rentedList
	// Returns the number of items returned
	unsigned int returnItem(const std::string& aItemID, unsigned int aNum);
	// Takes in a itemID, and returns a boolean of it is rented
	bool isRented(const std::string& aItemID);
private:
	// Customers id
	std::string customerID;
	// Customers name
	std::string customerName;
	// list of all current rents
	std::list<std::string> rentedList;
	// list of the nums of all current rents
	std::list<unsigned int> rentedListNum;
};

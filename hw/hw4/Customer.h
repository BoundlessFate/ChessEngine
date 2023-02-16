#include <string>
#include <list>
class Customer {
public:
	Customer(const std::string& aCustomerID, const std::string& aCustomerName);
	const std::string& getCustomerID() const {return customerID;}
	const std::string& getCustomerName() const {return customerName;}
	const std::list<std::string> getRentedList() const {return rentedList;}
	const std::list<unsigned int> getRentedListNum() const {return rentedListNum;}
	void rentItem(const std::string& aItemID, unsigned int aNum);
	unsigned int returnItem(const std::string& aItemID, unsigned int aNum);
	bool isRented(const std::string& aItemID);
private:
	std::string customerID;
	std::string customerName;
	std::list<std::string> rentedList;
	std::list<unsigned int> rentedListNum;
};

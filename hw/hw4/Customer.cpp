// Include the .h file for the object and iostream for cerr
#include "Customer.h"
#include <iostream>
// Constructor for the Customer object
Customer::Customer(const std::string& aCustomerID, const std::string& aCustomerName) {
	// Set customerID to the specified id
	customerID = aCustomerID;
	// Set customerName to the given name
	customerName = aCustomerName;
}
// rents item of the given id with the number specified
void Customer::rentItem(const std::string& aItemID, unsigned int aNum) {
	// Create iterators to go through the rentedList
	std::list<std::string>::iterator itItem;
	std::list<unsigned int>::iterator itNum;
	// Loop through the rentedList
	if (!rentedList.empty()) {
		for (itItem = rentedList.begin(), itNum = rentedListNum.begin(); 
				itItem != rentedList.end(); itItem++, itNum++) {
			// If the current index of rentedList is equal to the given itemID
			if (*itItem == aItemID) {
				// Add aNum to the number rented of that item id
				*itNum += aNum;
				// Return out to get out of the rest of the code
				return;
			}
		}
	}
	// below code only runs if aItemID is not in the rentedList
	// Add in the id to the end
	rentedList.push_back(aItemID);
	// Add the number you rented one index afterwards
	rentedListNum.push_back(aNum);
	// Exit out of the function
	return;
}
// Returns items, and returns the number of items returned
unsigned int Customer::returnItem(const std::string& aItemID, unsigned int aNum) {
	// Iterators to go through the list of rented items
	std::list<std::string>::iterator itItem;
	std::list<unsigned int>::iterator itNum;
	// Iterate through rentedList
	for (itItem = rentedList.begin(), itNum = rentedListNum.begin(); 
			itItem != rentedList.end(); itItem++, itNum++) {
		// If the id of the current indexd matches aItemID
		if (*itItem == aItemID) {
			// Check if the number of items attempted to be returned is more than they rented
			// If this is true, send a warning message and continue
			if (aNum > *itNum) {
				std::cerr << "Error: More Being Returned Than Is Checked Out." << std::endl;
				std::cerr << "Continuing By Changing aNum To Maximum." << std::endl;
				aNum = *itNum;
			}
			// Subtract the number of items they are renting with aNum
			*itNum -= aNum;
			// if the number of items they are renting is 0
			if (*itNum == 0) {
				// Erase the id and number indexes from rentedList
				rentedList.erase(itItem);
				rentedListNum.erase(itNum);
			}
			// Break out of the loop because youve already found the item with the id
			break;
		}
	}
	// Return amount returned
	return aNum;
}
// Returns a boolean if the itemid is currently being rented
bool Customer::isRented(const std::string& aItemID) {
	// Create an iterator for rentedList
	std::list<std::string>::iterator rentIt;
	// Iterate through rentedList
	for (rentIt = rentedList.begin(); 
			rentIt != rentedList.end(); rentIt++) {
		// If the id is found return true
		if (*rentIt == aItemID) {
			return true;
		}
	}
	// Return false if it isn't in the list
	return false;
}

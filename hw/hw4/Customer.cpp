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
	// Create an iterator to go throug the rentedList
	std::list<std::string>::iterator itItem;
	// Loop through the rentedList
	for (itItem = rentedList.begin(); itItem != rentedList.end(); itItem++) {
		// If the current index of rentedList is equal to the given itemID
		if (*itItem == aItemID) {
			// Go to the next index of itItem 
			// (the number of things the id is currently renting)
			itItem++;
			// Add aNum to the number rented of that item id
			*itItem = std::to_string(stoi(*itItem) + aNum);
			// Return out to get out of the rest of the code
			return;
		}
	}
	// below code only runs if aItemID is not in the rentedList
	// Add in the id to the end
	rentedList.push_back(aItemID);
	// Add the number you rented one index afterwards
	rentedList.push_back(std::to_string(aNum));
	// Exit out of the function
	return;
}
// Returns items, and returns the number of items returned
unsigned int Customer::returnItem(const std::string& aItemID, unsigned int aNum) {
	// Bool to see if the id was found in the list later on
	bool inList = false;
	// Iterator to go through the list of rented items
	std::list<std::string>::iterator itItem;
	// Iterate through rentedList
	for (itItem = rentedList.begin(); itItem != rentedList.end(); itItem++) {
		// If the id of the current indexd matches aItemID
		if (*itItem == aItemID) {
			// Set inList to true to say that the id has been found
			inList = true;
			// Create a second iterator to hold the spot of the number of objects
			std::list<std::string>::iterator itNum = itItem;
			itNum++;
			// Check if the number of items attempted to be returned is more than they rented
			// If this is true, send a warning message and continue
			if ((int)aNum > stoi(*itNum)) {
				std::cerr << "Error: More Being Returned Than Is Checked Out." << std::endl;
				std::cerr << "Continuing By Changing aNum To Maximum." << std::endl;
				aNum = stoi(*itNum);
			}
			// Subtract the number of items they are renting with aNum
			*itNum = std::to_string(stoi(*itNum) - aNum);
			// if the number of items they are renting is 0
			if (stoi(*itNum) == 0) {
				// Erase the id and number indexes from rentedList
				rentedList.erase(itItem);
				rentedList.erase(itNum);
			}
			// Break out of the loop because youve already found the item with the id
			break;
		}
	}
	// return the number of items that were removed
	if (inList) {
		return aNum;
	}
	return 0;
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

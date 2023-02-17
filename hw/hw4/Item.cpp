// Include the .h file for Item
#include "Item.h"
// Constructor for the item object
Item::Item(const std::string& aID, unsigned int aStock, const std::string& aName) {
	// Set ID to aID
	ID = aID;
	// Set stock to aStock
	stock = aStock;
	// Set name to aName
	name = aName;
}
// Add the id to the waitlist with the given number
void Item::addToWaitlist(const std::string& aID, unsigned int aNum) {
	// Push back the id
	waitlistID.push_back(aID);
	// Push back the requested number
	waitlistNum.push_back(aNum);
}
// Removes the maximum it can from the waitlist, 
// and returns the ids of the items it removed
std::list<std::string> Item::removeFromWaitlist() {
	// Create an iterator to go through the waitlist
	std::list<std::string>::iterator IDIterator;
	// Create an iterator to go through the waitlist nums
	std::list<unsigned int>::iterator numIterator;
	// Create a list to hold every id and num that left the waitlist
	std::list<std::string> waitlistRemoved;
	while(true) {
		// If checkToBreak stays true, the while loop is broken
		bool checkToBreak = true;
		// Iterate throug the waitlist
		for(IDIterator = waitlistID.begin(), numIterator = waitlistNum.begin();
				IDIterator != waitlistID.end() && numIterator != waitlistNum.end();
				IDIterator++, numIterator++) {
			// If there is enough stock to fufill the pending request
			if (*numIterator <= stock) {
				// Subtract the index from stock
				stock -= *numIterator;
				// Add the index and number to waitlistRemoved
				waitlistRemoved.push_back(*IDIterator);
				waitlistRemoved.push_back(std::to_string(*numIterator));
				// Erase the index and number form the waitlist
				waitlistNum.erase(numIterator);
				waitlistID.erase(IDIterator);
				// set checkToBreak to false,
				// repeating the loop again
				checkToBreak = false;
				// Break out of the for loop since 
				// you already found a good index
				break;
			}
		}
		// Check to break out of the while loop
		if (checkToBreak) {
			break;
		}
	}
	// Return the list of ids and numbers of stuff that
	// left the waitlist
	return waitlistRemoved;
}
// Add a id and number to the list of currently renting ids
void Item::addRentingList(const std::string& aID, unsigned int aNum) {
	// Create an iterator for rentingList
	std::list<std::string>::iterator rentingIterator;
	// Boolean to keep track if the id is already in rentingList
	bool alreadyIn = false;
	// Iterate through rentingList
	for (rentingIterator = rentingList.begin(); 
			rentingIterator != rentingList.end(); rentingIterator++) {
		// If the id matches the current Id in rentingList
		if (*rentingIterator == aID) {
			// Increase the value corresponding to that id by aNum
			rentingIterator++;
			*rentingIterator = std::to_string(stoi(*rentingIterator) + aNum);
			// Set alreadyIn to true since the id is already in the list
			alreadyIn = true;
			// Break out of the for loop
			break;
		}
	}
	// If the id is not in the list already
	if (!alreadyIn) {
		// Push the id and aNum to the back of rentingList
		rentingList.push_back(aID);
		rentingList.push_back(std::to_string(aNum));
	}
	// Exit out of the function
	return;
}
// Subtract an id and number from the list of currently renting ids
void Item::subtractRentingList(const std::string& aID, unsigned int aNum) {
	// Create an iterator for rentngList
	std::list<std::string>::iterator rentingIterator;
	// Boolean to keep track if the id is already in rentingList
	bool alreadyIn = false;
	// Iterate through rentingList
	for (rentingIterator = rentingList.begin(); 
			rentingIterator != rentingList.end(); rentingIterator++) {
		// If the id matches the current ID in rentingList
		if (*rentingIterator == aID) {
			// Decrease the value corresponding to that id by aNum
			rentingIterator++;
			*rentingIterator = std::to_string(stoi(*rentingIterator) - aNum);
			// Set alreadyIn to true since the id is already in the list
			alreadyIn = true;
			// Break out of the for loop
			break;
		}
	}
	// if the id isn't in rentedList
	if (!alreadyIn) {
		// display an error statement since this shouldn't happen
		std::cerr << "Error: Trying to return when there is no active ";
		std::cerr << "renter with the selected ID. Continuing..." << std::endl;
	}
	// Erase the values from rentingList if it is less than or equal to 0
	if (stoi(*rentingIterator) <= 0) {
		// Create a temporary iterator to hold the num value spot in memory
		std::list<std::string>::iterator tempIterator = rentingIterator;
		// Iterate rentingIterator to the id
		rentingIterator--;
		// Erase both the id and number
		rentingList.erase(rentingIterator);
		rentingList.erase(tempIterator);
	}
}

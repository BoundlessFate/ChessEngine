#include "Item.h"
Item::Item(const std::string& aID, unsigned int aStock, const std::string& aName) {
	ID = aID;
	stock = aStock;
	name = aName;
}
void Item::addToWaitlist(const std::string& aID, unsigned int aNum) {
	waitlistID.push_back(aID);
	waitlistNum.push_back(aNum);
}
std::list<std::string> Item::removeFromWaitlist() {
	std::list<std::string>::iterator IDIterator;
	std::list<unsigned int>::iterator numIterator;
	std::list<std::string> waitlistRemoved;
	while(true) {
		bool checkToContinue = true;
		for(IDIterator = waitlistID.begin(), numIterator = waitlistNum.begin();
				IDIterator != waitlistID.end() && numIterator != waitlistNum.end();
				IDIterator++, numIterator++) {
			if (*numIterator <= stock) {
				stock -= *numIterator;
				// Returned list will alternate between the id of the customer
				// and the amount they took out
				waitlistRemoved.push_back(*IDIterator);
				waitlistRemoved.push_back(std::to_string(*numIterator));
				waitlistNum.erase(numIterator);
				waitlistID.erase(IDIterator);
				checkToContinue = false;
				break;
			}
		}
		if (checkToContinue) {
			break;
		}
	}
	return waitlistRemoved;
}
void Item::addRentingList(const std::string& aID, unsigned int aNum) {
	std::list<std::string>::iterator rentingIterator;
	bool alreadyIn = false;
	for (rentingIterator = rentingList.begin(); rentingIterator != rentingList.end();
			rentingIterator++) {
		if (*rentingIterator == aID) {
			rentingIterator++;
			*rentingIterator = std::to_string(stoi(*rentingIterator) + aNum);
			break;
			alreadyIn = true;
		}
	}
	if (!alreadyIn) {
		rentingList.push_back(aID);
		rentingList.push_back(std::to_string(aNum));
	}
}
void Item::subtractRentingList(const std::string& aID, unsigned int aNum) {
	std::list<std::string>::iterator rentingIterator;
	bool alreadyIn = false;
	for (rentingIterator = rentingList.begin(); rentingIterator != rentingList.end();
			rentingIterator++) {
		if (*rentingIterator == aID) {
			rentingIterator++;
			*rentingIterator = std::to_string(stoi(*rentingIterator) - aNum);
			alreadyIn = true;
			break;
		}
	}
	if (!alreadyIn) {
		std::cerr << "Error: Trying to return when there is no person object. Continuing..." << std::endl;
	}
	if (stoi(*rentingIterator) <= 0) {
		std::list<std::string>::iterator tempIterator = rentingIterator;
		rentingIterator--;
		rentingList.erase(rentingIterator);
		rentingList.erase(tempIterator);
	}
}
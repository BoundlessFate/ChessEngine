#include <iostream>
#include <fstream>
#include <string.h>
#include "Item.h"
#include "Customer.h"
#include <list>
bool checkActive(const Customer& customer, std::list<Item>& items) {
	bool activeRent = !customer.getRentedList().empty();
	bool activeWaitlist = false;
	std::list<Item>::iterator itemIt;
	for (itemIt = items.begin(); itemIt != items.end(); itemIt++) {
		std::list<std::string> waitlistID = (*itemIt).getWaitlistID();
		std::list<std::string>::iterator waitlistIt;
		for (waitlistIt = waitlistID.begin(); waitlistIt != waitlistID.end(); waitlistIt++) {
			if (*waitlistIt == customer.getCustomerID()) {
				activeWaitlist = true;
				break;
			}
		}
		if (activeWaitlist) {
			break;
		}
	}
	if (activeRent && activeWaitlist) {
		return true;
	}
	return false;
}
void rentHandler(const std::string& customerID, unsigned int actionNum, 
		const std::string& toolID, const std::string& customerName, 
		std::list<Item>& itemList, std::list<Customer>& customerList) {
	std::list<Item>::iterator selectedItem;
	// Get the item that the customer tries to rent
	for (selectedItem = itemList.begin(); selectedItem != itemList.end(); selectedItem++) {
		if ((*selectedItem).getID() == toolID) {
			break;
		}
	}
	// Error out if item is not in list
	if (selectedItem == itemList.end()) {
		std::cerr << "Error: Item Not In List Of Items" << std::endl;
		return;
		// Error if the customer tries to rent 0 items
	} else if (actionNum == 0) {
		std::cerr << "Error: Trying To Rent 0 Items... Skipping Action" << std::endl;
		return;
	}
	if ((*selectedItem).getStock() >= actionNum) {
		std::list<Customer>::iterator selectedCustomer;
		bool inList = false;
		for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
			if ((*selectedCustomer).getCustomerID() == customerID) {
				inList = true;
				break;
			}
		}
		if (!inList) {
			for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
				if ((*selectedCustomer).getCustomerID() > customerID) {
					selectedCustomer = customerList.insert(selectedCustomer, Customer(customerID, customerName));
					inList = true;
					break;
				}
			}
			// Add Customer To List If They Arent Already In
			if (!inList) {
				customerList.push_back(Customer(customerID, customerName));
				selectedCustomer = customerList.end();
				selectedCustomer--;
			}
		}
		// Remove actionNum from stock, and add actionNum number of items to the customers current renting amount
		(*selectedItem).rentTool(actionNum);
		(*selectedItem).addRentingList((*selectedCustomer).getCustomerID(), actionNum);
		(*selectedCustomer).rentItem(toolID, actionNum);
	} else {
		// Add Customer To Waitlist For This Item
		(*selectedItem).addToWaitlist(customerID, actionNum);
		std::list<Customer>::iterator selectedCustomer;
		bool inList = false;
		for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
			if ((*selectedCustomer).getCustomerID() == customerID) {
				inList = true;
				break;
			}
		}
		// Add Customer To List If They Arent Already In
		if (!inList) {
			for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
				if ((*selectedCustomer).getCustomerID() > customerID) {
					selectedCustomer = customerList.insert(selectedCustomer, Customer(customerID, customerName));
					inList = true;
					break;
				}
			}
			if(!inList) {
				customerList.push_back(Customer(customerID, customerName));
			}
		}
	}
	return;
}
void returnHandler(const std::string& customerID, unsigned int actionNum, 
		const std::string& toolID, 
		std::list<Item>& itemList, std::list<Customer>& customerList) {
	std::list<Customer>::iterator selectedCustomer;
	// Get the customer that is returning the item
	for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
		if ((*selectedCustomer).getCustomerID() == customerID) {
			break;
		}
	}
	// Error out if customer is not in list
	if (selectedCustomer == customerList.end()) {
		std::cerr << "Error: Item Not In List Of Items" << std::endl;
		return;
		// Error if the customer tries to return 0 items
	} else if (actionNum == 0) {
		std::cerr << "Error: Trying To Return 0 Items... Skipping Action" << std::endl;
		return;
	}
	unsigned int amountReturned = (*selectedCustomer).returnItem(toolID, actionNum);
	if (!checkActive(*selectedCustomer, itemList)) {
		customerList.erase(selectedCustomer);
	}
	std::list<Item>::iterator selectedItem;
	// Get the item that the customer tries to rent
	for (selectedItem = itemList.begin(); selectedItem != itemList.end(); selectedItem++) {
		if ((*selectedItem).getID() == toolID) {
			break;
		}
	}
	(*selectedItem).returnTool(amountReturned);
	(*selectedItem).subtractRentingList((*selectedCustomer).getCustomerID(), amountReturned);
	std::list<std::string> exitWaitlist = (*selectedItem).removeFromWaitlist();
	std::list<std::string>::iterator exitWaitlistI = exitWaitlist.begin();
	for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
		if ((*selectedCustomer).getCustomerID() == *exitWaitlistI && exitWaitlistI != exitWaitlist.end()) {
			exitWaitlistI++;
			(*selectedCustomer).rentItem(toolID, stoi(*exitWaitlistI));
			(*selectedItem).addRentingList((*selectedCustomer).getCustomerID(), stoi(*exitWaitlistI));
			exitWaitlistI++;
		}
	}
	return;
}
void toolParser(const std::string& inputFile, std::list<Item>& itemList) {
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string toolID;
	unsigned int numStock;
	std::string toolName;
	unsigned int wordCount = 0;
	if(fileIn.is_open()) {
		while (fileIn >> currentWord) {
			if (wordCount == 0) {
				toolID = currentWord;
				wordCount += 1;
			} else if (wordCount == 1) {
				numStock = stoi(currentWord);
				wordCount += 1;
			} else {
				toolName = currentWord;
				std::list<Item>::iterator toolIt;
				bool inserted = false;
				for (toolIt = itemList.begin(); toolIt != itemList.end(); toolIt++) {
					if ((*toolIt).getID() > toolID) {
						itemList.insert(toolIt, Item(toolID, numStock, toolName));
						inserted = true;
						break;
					}
				}
				if (!inserted) {
					itemList.push_back(Item(toolID, numStock, toolName));
				}
				wordCount = 0;
			}
		}
	}
	return;
}
void customerParser(const std::string& inputFile, std::list<Item>& itemList, std::list<Customer>& customerList) {
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string customerID;
	std::string action;
	unsigned int actionNum;
	std::string toolID;
	std::string customerName;
	unsigned int wordCount = 0;
	if(fileIn.is_open()) {
		while (fileIn >> currentWord) {
			if (wordCount == 0) {
				customerID = currentWord;
				wordCount += 1;
			} else if (wordCount == 1) {
				action = currentWord;
				wordCount += 1;
			} else if (wordCount == 2) {
				wordCount += 1;
			} else if (wordCount == 3) {
				actionNum = stoi(currentWord);
				wordCount += 1;
			} else if (wordCount == 4) {
				toolID = currentWord;
				wordCount += 1;
			} else {
				customerName = currentWord;
				if (action == "rent") {
					rentHandler(customerID, actionNum, toolID, 
							customerName, itemList, customerList);
				} else if (action == "return") {
					returnHandler(customerID, actionNum, toolID, 
							itemList, customerList);
				} else {
					std::cerr << "Error: Incorrect Customer Action Selected" << std::endl;
				}
				wordCount = 0;
			}
		}
	}
	return;
}
void inventoryOutput(const std::string& file, std::list<Item>& itemList,
		std::list<Customer>& customerList) {
	std::ofstream outFile;
	outFile.open(file, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	outFile.open(file, std::ios_base::app);
	std::list<Item>::iterator it;
	for (it = itemList.begin(); it != itemList.end(); it++) {
		std::list<std::string> waitlistCustomers = (*it).getWaitlistID();
		std::list<unsigned int> waitlistCustomersNum = (*it).getWaitlistNum();
		std::list<std::string> rentCustomers = (*it).getRentingList();
		outFile << (*it).getID() << " " << (*it).getStock();
		outFile << " available " << (*it).getName() << std::endl;
		if (!rentCustomers.empty()) {
			outFile << "Rental Customers: ";
			std::list<std::string>::iterator rentIt;
			std::list<std::string> outputList;
			std::list<std::string>::iterator outputIt;
			for (rentIt = rentCustomers.begin(); rentIt != rentCustomers.end();
					rentIt++) {
				std::string currentOutput;
				currentOutput += *rentIt;
				currentOutput += " ";
				std::list<Customer>::iterator customerIt;
				for (customerIt = customerList.begin(); 
						customerIt != customerList.end(); customerIt++) {
					if ((*customerIt).getCustomerID() == *rentIt) {
						currentOutput += (*customerIt).getCustomerName();
					}
				}
				rentIt++;
				currentOutput += " (";
				currentOutput += *rentIt;
				currentOutput += ") ";
				bool inserted = false;
				for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
					if (*outputIt > currentOutput) {
						outputList.insert(outputIt, currentOutput);
						inserted = true;
						break;
					}
				}
				if (!inserted) {
					outputList.push_back(currentOutput);
				}
			}
			for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		if (!waitlistCustomers.empty()) {
			outFile << "Pending Customers: ";
			std::list<std::string>::iterator waitlistIt;
			std::list<unsigned int>::iterator waitlistNumIt;
			std::list<std::string> outputList;
			std::list<std::string>::iterator outputIt;
			for (waitlistIt = waitlistCustomers.begin(), waitlistNumIt = waitlistCustomersNum.begin();
					waitlistIt != waitlistCustomers.end();
					waitlistIt++, waitlistNumIt++) {
				std::string currentOutput;
				currentOutput += *waitlistIt;
				currentOutput += " ";
				std::list<Customer>::iterator customerIt;
				for (customerIt = customerList.begin(); 
						customerIt != customerList.end(); customerIt++) {
					if ((*customerIt).getCustomerID() == *waitlistIt) {
						currentOutput += (*customerIt).getCustomerName();
					}
				}
				currentOutput += " (";
				currentOutput += std::to_string(*waitlistNumIt);
				currentOutput += ") ";
				bool inserted = false;
				for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
					if (*outputIt > currentOutput) {
						outputList.insert(outputIt, currentOutput);
						inserted = true;
						break;
					}
				}
				if (!inserted) {
					outputList.push_back(currentOutput);
				}
			}
			for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		outFile << std::endl;
	}
}
void customerOutput(const std::string& file, std::list<Item>& itemList,
		std::list<Customer>& customerList) {
	std::ofstream outFile;
	outFile.open(file, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	outFile.open(file, std::ios_base::app);
	std::list<Customer>::iterator it;
	for (it = customerList.begin(); it != customerList.end(); it++) {
		outFile << (*it).getCustomerID() << " ";
		outFile << (*it).getCustomerName() << std::endl;
		std::list<std::string> rentList;
		std::list<std::string> waitlist;
		std::list<Item>::iterator itItem;
		// Iterate through all the items
		for(itItem = itemList.begin(); itItem != itemList.end(); itItem++) {
			std::list<std::string>::iterator rentListIt;
			std::list<std::string> rentingList = (*itItem).getRentingList();
			std::string currentOutput;
			std::list<std::string>::iterator outputIt;
			for(rentListIt = rentingList.begin(); 
					rentListIt != rentingList.end(); rentListIt++) {
				if (*rentListIt == (*it).getCustomerID()) {
					currentOutput += (*itItem).getID();
					currentOutput += " (";
					rentListIt++;
					currentOutput += *rentListIt;
					currentOutput += ") ";
					bool inserted = false;
					for (outputIt = rentList.begin(); outputIt != rentList.end(); outputIt++) {
						if (*outputIt > currentOutput) {
							rentList.insert(outputIt, currentOutput);
							inserted = true;
							break;
						}
					}
					if (!inserted) {
						rentList.push_back(currentOutput);
					}
					break;
				}
			}
			std::list<std::string> waitlistIDs = (*itItem).getWaitlistID();
			std::list<unsigned int> waitlistNums = (*itItem).getWaitlistNum();
			std::list<std::string>::iterator waitIDIt;
			std::list<unsigned int>::iterator waitNumIt;
			std::string waitOutput;
			for (waitIDIt = waitlistIDs.begin(), waitNumIt = waitlistNums.begin(); 
					waitIDIt != waitlistIDs.end(); 
					waitIDIt++, waitNumIt++) {
				if (*waitIDIt == (*it).getCustomerID()) {
					waitOutput += (*itItem).getID();
					waitOutput += " (";
					waitOutput += std::to_string(*waitNumIt);
					waitOutput += ") ";
					bool inserted = false;
					for (outputIt = waitlist.begin(); outputIt != waitlist.end(); outputIt++) {
						if (*outputIt > currentOutput) {
							waitlist.insert(outputIt, waitOutput);
							inserted = true;
							break;
						}
					}
					if (!inserted) {
						waitlist.push_back(waitOutput);
					}
					break;
				}
			}
			
		}
		if (!rentList.empty()) {
			outFile << "Rentals: ";
			std::list<std::string>::iterator outputIt;
			for (outputIt = rentList.begin(); 
					outputIt != rentList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		if (!waitlist.empty()) {
			outFile << "Pending: ";
			std::list<std::string>::iterator outputIt;
			for (outputIt = waitlist.begin(); 
					outputIt != waitlist.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		outFile << std::endl;
	}
}
int main(int argc, char** argv) {
	if (argc == 5) {
		std::list<Item> itemList;
		std::list<Customer> customerList;
		std::string toolFile = argv[1];
		std::string customerFile = argv[2];
		std::string inventoryOutputFile = argv[3];
		std::string customerOutputFile = argv[4];
		toolParser(toolFile, itemList);
		customerParser(customerFile, itemList, customerList);
		inventoryOutput(inventoryOutputFile, itemList, customerList);
		customerOutput(customerOutputFile, itemList, customerList);
	}
	return 1;
}

#include <iostream>
#include <fstream>
#include <string.h>
#include "Item.h"
#include "Customer.h"
#include <list>
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
		for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
			if ((*selectedCustomer).getCustomerID() == customerID) {
				break;
			}
		}
		// Add Customer To List If They Arent Already In
		if (selectedCustomer == customerList.end()) {
			customerList.push_back(Customer(customerID, customerName));
			selectedCustomer = customerList.end();
			selectedCustomer--;
		}

		// Remove actionNum from stock, and add actionNum number of items to the customers current renting amount
		(*selectedItem).rentTool(actionNum);
		(*selectedCustomer).rentItem(toolID, actionNum);
	} else {
		// Add Customer To Waitlist For This Item
		(*selectedItem).addToWaitlist(customerID, actionNum);
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
	std::list<Item>::iterator selectedItem;
	// Get the item that the customer tries to rent
	for (selectedItem = itemList.begin(); selectedItem != itemList.end(); selectedItem++) {
		if ((*selectedItem).getID() == toolID) {
			break;
		}
	}
	(*selectedItem).returnTool(amountReturned);
	std::list<std::string> exitWaitlist = (*selectedItem).removeFromWaitlist();
	std::list<std::string>::iterator exitWaitlistI = exitWaitlist.begin();
	for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
		if ((*selectedCustomer).getCustomerID() == *exitWaitlistI && exitWaitlistI != exitWaitlist.end()) {
			exitWaitlistI++;
			(*selectedCustomer).rentItem(toolID, stoi(*exitWaitlistI));
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
				itemList.push_back(Item(toolID, numStock, toolName));
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
	/* unsigned int timestamp; */
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
				/* timestamp = stoi(currentWord); */
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
void inventoryOutput(const std::string& file, std::list<Item>& itemList) {
	std::ofstream outFile;
	outFile.open(file, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	outFile.open(file, std::ios_base::app);
	std::list<Item>::iterator it;
	for (it = itemList.begin(); it != itemList.end(); it++) {
		outFile << (*it).getID() << " " << (*it).getStock();
		outFile << " available " << (*it).getName() << std::endl;
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
		inventoryOutput(inventoryOutputFile, itemList);

	}
	return 1;
}

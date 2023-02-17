// iostream for std::cerr
#include <iostream>
// fstream for file editing
#include <fstream>
// string.h for std::string
#include <string.h>
// Item and Customer class files
#include "Item.h"
#include "Customer.h"
// List for std::list<T> and std::list<T>::iterator
#include <list>
// Returns true or false if the id is a valid tool id
bool checkValidToolID(const std::string& toolID) {
	// Set valid to true
	bool valid = true;
	// If the first letter isnt a T
	if (!(toolID[0] == 'T')) {
		// Set valid to false
		valid = false;
	}
	// If the number associated with it isnt 4 digits
	std::string idStringNum = toolID.substr(1);
	if (!(idStringNum.size() == 4)) {
		// Set valid to false
		valid =  false;
	}
	// If any of the characters from the 1st character onwards
	// arent digits
	for (unsigned int i=0; i<idStringNum.size(); i++) {
		if (!isdigit(idStringNum[i])) {
			// Set valid to false
			valid = false;
		}
	}
	// Convert idStringNum to an integer
	if (valid) {
		// if idNum isnt greater than 0
		int idNum = stoi(idStringNum);
		if (!(idNum > 0)) {
			// Set valid to false
			valid = false;
		}
	}
	// If valid is false
	if (!valid) {
		// Create the error statement
		std::cerr << "Invalid inventory ID ";
		std::cerr << toolID;
		std::cerr << " found in the inventory file.";
		std::cerr << std::endl;
		// Return false
		return false;
	}
	// Return true if valid is true
	return true;
}
// Returns true or false if the customer id is valid
bool checkValidCustomerID(const std::string& customerID) {
	// If this stays true, id is valid
	bool valid = true;
	// If the first letter is not C
	if (!(customerID[0] == 'C')) {
		// Set valid to false
		valid = false;
	}
	// Get the rest of the id
	std::string idStringNum = customerID.substr(1);
	// If the rest of the id isnt 4 characters
	if (!(idStringNum.size() == 4)) {
		// Set valid to false
		valid =  false;
	}
	// Iterate through the rest of the id
	for (unsigned int i=0; i<idStringNum.size(); i++) {
		// If any of the characters arent a digit
		if (!isdigit(idStringNum[i])) {
			// Set valid to false
			valid = false;
		}
	}
	// Convert the rest of the characters into an integer
	if (valid) {
		int idNum = stoi(idStringNum);
		// If the number is not above 0
		if (!(idNum > 0)) {
			// Set valid to false
			valid = false;
		}
	}
	// If the id is not valid
	if (!valid) {
		// Create the error statement
		std::cerr << "Invalid customer information found";
		std::cerr << " for ID ";
		std::cerr << customerID;
		std::cerr << " in the customer file.";
		std::cerr << std::endl;
		// Return false
		return false;
	}
	// If the id is valid, return true
	return true;
}
// Returns a boolean of it the item is in the inventory
bool checkRequestedItem(const std::string& customerID, 
		const std::string& itemID, std::list<Item>& itemList, 
		const std::string& action) {
	// Create a bool to see if the item is in inventory
	bool valid = false;
	// Create an iterator for the itemList
	std::list<Item>::iterator itemIt;
	// Iterate through itemList
	for (itemIt = itemList.begin(); itemIt != itemList.end(); itemIt++) {
		// If the id matches the current items id
		if ((*itemIt).getID() == itemID) {
			// Set valid to true
			valid = true;
			// Break out of the for loop
			break;
		}
	}
	// If the item is not valid
	if (!valid) {
		// Display error statements based on the action
		if (action == "rent") {
			std::cerr << "Customer " << customerID;
			std::cerr << " requested item " << itemID;
			std::cerr << " which is not in the inventory.";
			std::cerr << std::endl;
		} else if (action == "return") {
			std::cerr << "Customer " << customerID;
			std::cerr << " attempted to return item ";
			std::cerr << itemID;
			std::cerr << " which is not in the inventory.";
			std::cerr << std::endl;
		}
		// Return false for invalid
		return false;
	}
	// Return true because the item is in the list
	return true;
}
// Function that helps with the Customer function isRented()
bool checkIfRented(const std::string& customerID, 
		const std::string& itemID, std::list<Customer>& customerList) {
	// Create an iterator for the customers
	std::list<Customer>::iterator customerIt;
	// Iterate through the customers
	for (customerIt = customerList.begin(); 
			customerIt != customerList.end(); customerIt++) {
		// If the customer id mtaches the target
		if ((*customerIt).getCustomerID() == customerID) {
			// Return if the selected customer is renting
			return ((*customerIt).isRented(itemID));
		}
	}
	// return false
	return false;
}

bool checkActive(const Customer& customer, std::list<Item>& items) {
	// Boolean for if the customer is renting something
	bool activeRent = !customer.getRentedList().empty();
	// Boolean for if the customer is on a waitlist
	bool activeWaitlist = false;
	// Iterator for all items
	std::list<Item>::iterator itemIt;
	// Iterate through all items
	for (itemIt = items.begin(); itemIt != items.end(); itemIt++) {
		// gather the waitlist for the item
		std::list<std::string> waitlistID = (*itemIt).getWaitlistID();
		// Create an iterator for the items waitlist
		std::list<std::string>::iterator waitlistIt;
		// Iterate through the items waitlist
		for (waitlistIt = waitlistID.begin(); 
				waitlistIt != waitlistID.end(); waitlistIt++) {
			// If the person is in the waitlist
			if (*waitlistIt == customer.getCustomerID()) {
				// Set activeWaitlist to true
				activeWaitlist = true;
				// Break out of the waitlist for loop
				break;
			}
		}
		// Break out of the items for loop if the customer
		// Was found in a waitlist
		if (activeWaitlist) {
			break;
		}
	}
	// If the person is actively renting or
	// actively on a waitlist
	if (activeRent || activeWaitlist) {
		// Return true
		return true;
	}
	// if they aren't active, return false
	return false;
}
// Takes in a customers name and ID, and inserts them into the list in order
void addCustomerToCustomerList(const std::string& customerID, 
		const std::string& customerName, std::list<Customer>& customerList) {
	std::list<Customer>::iterator selectedCustomer;
	// Boolean for if the customer is in the list
	bool inList = false;
	// Iterate through the customerList
	for (selectedCustomer = customerList.begin(); 
			selectedCustomer != customerList.end(); selectedCustomer++) {
		// Set inList to true if the customers id matches
		// the current Customer id
		if ((*selectedCustomer).getCustomerID() == customerID) {
			inList = true;
			// Break out of the for loop
			break;
		}
	}
	// Add Customer To List If They Arent Already In
	if (!inList) {
		// Iterate through the customerList
		for (selectedCustomer = customerList.begin(); selectedCustomer != customerList.end(); selectedCustomer++) {
			// Insert the customer based on id
			if ((*selectedCustomer).getCustomerID() > customerID) {
				selectedCustomer = customerList.insert(selectedCustomer, Customer(customerID, customerName));
				// Set inList to true
				inList = true;
				// Break out of the for loop
				break;
			}
		}
		// if the customer still isn't in the list
		// Add them to the end
		if(!inList) {
			customerList.push_back(Customer(customerID, customerName));
		}
	}
}
// Function to handle renting from the customer file
void rentHandler(const std::string& customerID, unsigned int actionNum, 
		const std::string& toolID, const std::string& customerName, 
		std::list<Item>& itemList, std::list<Customer>& customerList) {
	// Create an iterator for the itemList
	std::list<Item>::iterator selectedItem;
	// Get the item that the customer tries to rent
	for (selectedItem = itemList.begin(); selectedItem != itemList.end(); selectedItem++) {
		if ((*selectedItem).getID() == toolID) {
			break;
		}
	}
	// Check if there is enough stock for renting it
	if ((*selectedItem).getStock() >= actionNum) {
		addCustomerToCustomerList(customerID, customerName, customerList);
		// Create an iterator for customers
		std::list<Customer>::iterator selectedCustomer;
		// Set selectedCustomers to the customer with
		// the matching id
		for (selectedCustomer = customerList.begin(); 
				selectedCustomer != customerList.end(); selectedCustomer++) {
			if ((*selectedCustomer).getCustomerID() == customerID) {
				break;
			}
		}
		// rent the tool from the item class
		(*selectedItem).rentTool(actionNum);
		// Add the customer to the renting list in the item class
		(*selectedItem).addRentingList((*selectedCustomer).getCustomerID(), actionNum);
		// rent the item in the Customer class
		(*selectedCustomer).rentItem(toolID, actionNum);
		// If the person wanted to rent but there wasn't enough stock
	} else {
		// Add Customer To Waitlist For This Item
		(*selectedItem).addToWaitlist(customerID, actionNum);
		addCustomerToCustomerList(customerID, customerName, customerList);
	}
	return;
}
// Handles all returns when called upon
void returnHandler(const std::string& customerID, unsigned int actionNum, 
		const std::string& toolID, 
		std::list<Item>& itemList, std::list<Customer>& customerList) {
	// Create an iterator for the Customers
	std::list<Customer>::iterator selectedCustomer;
	// Get the customer that is returning the item
	for (selectedCustomer = customerList.begin(); 
			selectedCustomer != customerList.end(); selectedCustomer++) {
		if ((*selectedCustomer).getCustomerID() == customerID) {
			// Break out of the for loop
			break;
		}
	}
	// returns items in the Customer class
	// How much it returned is set as amountReturned
	unsigned int amountReturned = (*selectedCustomer).returnItem(toolID, actionNum);
	// Erase the customer from customerList if they 
	// arent renting or on any waitlists
	if (!checkActive(*selectedCustomer, itemList)) {
		customerList.erase(selectedCustomer);
	}
	// Create an iterator for itemList
	std::list<Item>::iterator selectedItem;
	// Get the item that the customer tries to rent
	for (selectedItem = itemList.begin(); selectedItem != itemList.end(); selectedItem++) {
		if ((*selectedItem).getID() == toolID) {
			break;
		}
	}
	// Return the tool in the selectedItems class
	(*selectedItem).returnTool(amountReturned);
	// Subtract the customers spot in the items list by amountReturned
	(*selectedItem).subtractRentingList((*selectedCustomer).getCustomerID(), amountReturned);
	// Set exitWaitlist to everyone that should leave the waitlist
	std::list<std::string> exitWaitlist = (*selectedItem).removeFromWaitlist();
	// Create an iterator for the exitWaitlist
	// Set it to the first index
	std::list<std::string>::iterator exitWaitlistI = exitWaitlist.begin();
	// Iterate through customerList
	for (selectedCustomer = customerList.begin(); 
			selectedCustomer != customerList.end(); selectedCustomer++) {
		// If the customer selected is in the current index of exitWaitlist
		if ((*selectedCustomer).getCustomerID() == *exitWaitlistI &&
				exitWaitlistI != exitWaitlist.end()) {
			// change exitWaitlistI to be the value that the person wanted
			exitWaitlistI++;
			// Have the customer rent items of the amount they wanted
			(*selectedCustomer).rentItem(toolID, stoi(*exitWaitlistI));
			// Add the customer to the items renting list
			(*selectedItem).addRentingList((*selectedCustomer).getCustomerID(), stoi(*exitWaitlistI));
			// Set exitWaitlistI to be the next ID
			exitWaitlistI++;
		}
	}
	// Exit out of the function
	return;
}
// Parses through the tool file
void toolParser(const std::string& inputFile, std::list<Item>& itemList) {
	// Open the file and get starting variables
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string toolID;
	unsigned int numStock;
	std::string toolName;
	// wordCount tracks the current word on a line
	unsigned int wordCount = 0;
	if(fileIn.is_open()) {
		bool valid = true;
		// Loop through the file and set currentWord to the next word
		while (fileIn >> currentWord) {
			// If currentWord is the toolID
			if (wordCount == 0) {
				toolID = currentWord;
				// Check if the toolID is valid
				valid = checkValidToolID(toolID);
				wordCount += 1;
			// If currentWord is the numStock
			} else if (wordCount == 1) {
				numStock = stoi(currentWord);
				wordCount += 1;
			// If currentWord is the toolName
			} else {
				toolName = currentWord;
				// If the line is valid
				if (valid) {
					// Iterator for the list of items
					std::list<Item>::iterator toolIt;
					bool inserted = false;
					// Iterate through the item list
					for (toolIt = itemList.begin(); 
							toolIt != itemList.end(); toolIt++) {
						// Insert the item in the proper spot by id
						if ((*toolIt).getID() > toolID) {
							itemList.insert(toolIt, Item(toolID, numStock, toolName));
							// Set inserted to true
							inserted = true;
							// Break out of the for loop
							break;
						}
					}
					// If the item still hasnt been inserted
					if (!inserted) {
						// Add the item to the last index
						itemList.push_back(Item(toolID, numStock, toolName));
					}
				}
				// Set wordCount to 0 in preparation
				// for a new line
				wordCount = 0;
			}
		}
	}
	// Get out of the function
	return;
}
// Parse through the customer file
void customerParser(const std::string& inputFile, std::list<Item>& itemList, std::list<Customer>& customerList) {
	// Starting variables
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string customerID;
	std::string action;
	unsigned int actionNum;
	std::string toolID;
	std::string customerName;
	// Word count to keep track of the word on a line
	unsigned int wordCount = 0;
	if(fileIn.is_open()) {
		bool valid = true;
		while (fileIn >> currentWord) {
			// if currentWord is customerID
			if (wordCount == 0) {
				customerID = currentWord;
				// Check that the customerID is valid
				valid = checkValidCustomerID(customerID);
				wordCount += 1;
			// if currentWord is action
			} else if (wordCount == 1) {
				action = currentWord;
				wordCount += 1;
			// This word is timestamp, but it was unused
			} else if (wordCount == 2) {
				wordCount += 1;
			// if currentWord is actionNum
			} else if (wordCount == 3) {
				actionNum = stoi(currentWord);
				wordCount += 1;
			// If currentWord is toolID
			} else if (wordCount == 4) {
				toolID = currentWord;
				// Check if the requested item is valid
				if (!checkRequestedItem(customerID, toolID, itemList, action)) {
					valid = false;
				}
				wordCount += 1;
			// if currentWord is customerName
			} else {
				customerName = currentWord;
				// If the line is valid
				if (valid) {
					// If the action is rent
					if (action == "rent") {
						// do rent actions
						rentHandler(customerID, actionNum, toolID, 
								customerName, itemList, customerList);
					// If the action is return
					} else if (action == "return") {
						// do return actions if and only if they rented the item
						if (checkIfRented(customerID, toolID, customerList)) {
							returnHandler(customerID, actionNum, toolID, 
									itemList, customerList);
						}
						else {
							// Error statements
							std::cerr << "Customer " << customerID;
							std::cerr << " attempted to return item ";
							std::cerr << toolID << " which she/he did not rent.";
							std::cerr << std::endl;
						}
					} else {
						// Error statement on action type
						std::cerr << "Error: Incorrect Customer Action Selected" << std::endl;
					}
				}
				// Set word count in preparation for a new line
				wordCount = 0;
			}
		}
	}
	// Get out of the function
	return;
}
// Output to the inventory output file
void inventoryOutput(const std::string& file, std::list<Item>& itemList,
		std::list<Customer>& customerList) {
	// Delete all contents from the file
	std::ofstream outFile;
	outFile.open(file, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	// Reopen the file
	outFile.open(file, std::ios_base::app);
	// Create an iterator and iterate through all items in itemList
	std::list<Item>::iterator it;
	for (it = itemList.begin(); it != itemList.end(); it++) {
		std::list<std::string> waitlistCustomers = (*it).getWaitlistID();
		std::list<unsigned int> waitlistCustomersNum = (*it).getWaitlistNum();
		std::list<std::string> rentCustomers = (*it).getRentingList();
		// Base output line for a item
		outFile << (*it).getID() << " " << (*it).getStock();
		outFile << " available " << (*it).getName() << std::endl;
		// If the item is being rented
		if (!rentCustomers.empty()) {
			// Output to file
			outFile << "Rental Customers: ";
			// Create an iterator for rentCustomers
			std::list<std::string>::iterator rentIt;
			// Create a new list outputList and an iterator for it
			std::list<std::string> outputList;
			std::list<std::string>::iterator outputIt;
			// Iterate through rentCustomers
			for (rentIt = rentCustomers.begin(); rentIt != rentCustomers.end();
					rentIt++) {
				// Build the currentOutput string
				std::string currentOutput;
				currentOutput += *rentIt;
				currentOutput += " ";
				// Create an iterator for customerList
				std::list<Customer>::iterator customerIt;
				// Iterate through customerList
				for (customerIt = customerList.begin(); 
						customerIt != customerList.end(); customerIt++) {
					// If the current customer is the current index
					// in rentCustomers
					if ((*customerIt).getCustomerID() == *rentIt) {
						// Add their name to currentOutput
						currentOutput += (*customerIt).getCustomerName();
						break;
					}
				}
				// Go to the customers value in rentCustomers
				rentIt++;
				// Add to currentOutput
				currentOutput += " (";
				currentOutput += *rentIt;
				currentOutput += ") ";
				// Insert currentOutput in outputList alphabetically
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
			// Loop through the outputList
			// Output the list in order to outFile
			for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		// If the waitlist isn't empty
		if (!waitlistCustomers.empty()) {
			// Output to outFile
			outFile << "Pending Customers: ";
			// Create waitlist iterators
			std::list<std::string>::iterator waitlistIt;
			std::list<unsigned int>::iterator waitlistNumIt;
			std::list<std::string> outputList;
			std::list<std::string>::iterator outputIt;
			// Iterate through waitlist
			for (waitlistIt = waitlistCustomers.begin(), 
					waitlistNumIt = waitlistCustomersNum.begin();
					waitlistIt != waitlistCustomers.end(); waitlistIt++, waitlistNumIt++) {
				// Create a string for the current output
				std::string currentOutput;
				// Add the Customer ID to the currentOutput
				currentOutput += *waitlistIt;
				currentOutput += " ";
				// add the id's name to the currentOutput
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
				// Insert currentOutput into the outputList alphebetically
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
			// Output the outputList in order
			for (outputIt = outputList.begin(); outputIt != outputList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		// Add a line between each item
		outFile << std::endl;
	}
}
// Output to the customer file
void customerOutput(const std::string& file, std::list<Item>& itemList,
		std::list<Customer>& customerList) {
	// Empty the file
	std::ofstream outFile;
	outFile.open(file, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	outFile.open(file, std::ios_base::app);
	// Iterate through all customers in customerList
	std::list<Customer>::iterator it;
	for (it = customerList.begin(); it != customerList.end(); it++) {
		// Output information to outFile
		outFile << (*it).getCustomerID() << " ";
		outFile << (*it).getCustomerName() << std::endl;
		std::list<std::string> rentList;
		std::list<std::string> waitlist;
		std::list<Item>::iterator itItem;
		// Iterate through all the items
		for(itItem = itemList.begin(); itItem != itemList.end(); itItem++) {
			std::list<std::string>::iterator rentListIt;
			// Get a list of all customers that rent the item
			std::list<std::string> rentingList = (*itItem).getRentingList();
			// create the currentOutput string
			std::string currentOutput;
			// Iterate through all customers in rentingList
			std::list<std::string>::iterator outputIt;
			for(rentListIt = rentingList.begin(); 
					rentListIt != rentingList.end(); rentListIt++) {
				// If the current customer is renting this item
				if (*rentListIt == (*it).getCustomerID()) {
					// add information to currentOutput
					currentOutput += (*itItem).getID();
					currentOutput += " (";
					rentListIt++;
					currentOutput += *rentListIt;
					currentOutput += ") ";
					// Insert currentOutput to the rentList
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
			// Get the waitlist for the current item
			std::list<std::string> waitlistIDs = (*itItem).getWaitlistID();
			std::list<unsigned int> waitlistNums = (*itItem).getWaitlistNum();
			// Create an iterator for the waitlist
			std::list<std::string>::iterator waitIDIt;
			std::list<unsigned int>::iterator waitNumIt;
			// Create an output string
			std::string waitOutput;
			// Iterate through waitlist
			for (waitIDIt = waitlistIDs.begin(), waitNumIt = waitlistNums.begin(); 
					waitIDIt != waitlistIDs.end();
					waitIDIt++, waitNumIt++) {
				// If the id in waitlist is the same as the customer
				if (*waitIDIt == (*it).getCustomerID()) {
					waitOutput += (*itItem).getID();
					waitOutput += " (";
					waitOutput += std::to_string(*waitNumIt);
					waitOutput += ") ";
					// Insert waitOutput to the waitOutputList
					bool inserted = false;
					for (outputIt = waitlist.begin(); 
							outputIt != waitlist.end(); outputIt++) {
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
		// If there were things rented
		if (!rentList.empty()) {
			// Output info to outFile
			outFile << "Rentals: ";
			std::list<std::string>::iterator outputIt;
			for (outputIt = rentList.begin(); 
					outputIt != rentList.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		// If there were things in waitOutputList
		if (!waitlist.empty()) {
			// Output info to outFile
			outFile << "Pending: ";
			std::list<std::string>::iterator outputIt;
			for (outputIt = waitlist.begin(); 
					outputIt != waitlist.end(); outputIt++) {
				outFile << *outputIt;
			}
			outFile << std::endl;
		}
		// Output an extra line between Customers
		outFile << std::endl;
	}
}
// Main code that gets run between all the files
int main(int argc, char** argv) {
	// If there is the right amount of arguments
	if (argc == 5) {
		// Create an empty itemList
		std::list<Item> itemList;
		// Create an empty customerList
		std::list<Customer> customerList;
		// set variables to argv
		std::string toolFile = argv[1];
		std::string customerFile = argv[2];
		std::string inventoryOutputFile = argv[3];
		std::string customerOutputFile = argv[4];
		// Parse the tool file
		toolParser(toolFile, itemList);
		// Parse the customer file
		customerParser(customerFile, itemList, customerList);
		// output to the inventory file
		inventoryOutput(inventoryOutputFile, itemList, customerList);
		// output to the customer file
		customerOutput(customerOutputFile, itemList, customerList);
	}
	// exit out of main
	return 1;
}

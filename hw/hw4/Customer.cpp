#include "Customer.h"
#include <iostream>
Customer::Customer(const std::string& aCustomerID, const std::string& aCustomerName) {
	customerID = aCustomerID;
	customerName = aCustomerName;
}
void Customer::rentItem(const std::string& aItemID, unsigned int aNum) {
	std::list<std::string>::iterator itItem;
	std::list<unsigned int>::iterator itNum;
	for (itItem = rentedList.begin(), itNum = rentedListNum.begin(); itItem != rentedList.end(); itItem++, itNum++) {
		if (*itItem == aItemID) {
			*itNum += aNum;
			return;
		}
	}
	rentedList.push_back(aItemID);
	rentedListNum.push_back(aNum);
	return;
}
unsigned int Customer::returnItem(const std::string& aItemID, unsigned int aNum) {
	std::list<std::string>::iterator itItem;
	std::list<unsigned int>::iterator itNum;
	for (itItem = rentedList.begin(), itNum = rentedListNum.begin(); itItem != rentedList.end(); itItem++, itNum++) {
		if (*itItem == aItemID) {
			if (aNum > *itNum) {
				std::cerr << "Error: More Being Returned Than Is Checked Out." << std::endl;
				std::cerr << "Continuing By Changing aNum To Maximum." << std::endl;
				aNum = *itNum;
			}
			*itNum -= aNum;
			if (*itNum == 0) {
				rentedList.erase(itItem);
				rentedListNum.erase(itNum);
			}
			break;
		}
	}
	return *itNum;
}

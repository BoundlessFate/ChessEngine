#include "Item.h"
class Customer {
public:
	list<Item> currentlyRenting();
	list<Item> waitlistedItems();
	void customerReturnItem();
	~Customer
private:
	list<Item> itemsRented;
	list<Item> waitlistedItems();
};

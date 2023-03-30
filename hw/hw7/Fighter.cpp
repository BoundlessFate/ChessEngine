#include "Fighter.h"
Fighter::Fighter(std::string aName, int aJabTime, int aFtiltTime, int aUtiltTime, int aDtiltTime, int aFsmashTime, int aUsmashTime, int aDsmashTime) {
	name = aName;
	jabTime = aJabTime;
	ftiltTime = aFtiltTime;
	utiltTime = aUtiltTime;
	dtiltTime = aDtiltTime;
	fsmashTime = aFsmashTime;
	usmashTime = aUsmashTime;
	dsmashTime = aDsmashTime;
}

// Include statements
#include "Fighter.h"
#include <iostream>
// Constructor
Fighter::Fighter(std::string aName, int aJabTime, int aFtiltTime, int aUtiltTime,
		int aDtiltTime, int aFsmashTime, int aUsmashTime, int aDsmashTime) {
	// Set initial data
	name = aName;
	jabTime = aJabTime;
	ftiltTime = aFtiltTime;
	utiltTime = aUtiltTime;
	dtiltTime = aDtiltTime;
	fsmashTime = aFsmashTime;
	usmashTime = aUsmashTime;
	dsmashTime = aDsmashTime;
}
// Get the data for the current move
int Fighter::GetMoveTime() const {
	if (move == "jab")
		return jabTime;
	if (move == "forward-tilt")
		return ftiltTime;
	if (move == "up-tilt")
		return utiltTime;
	if (move == "down-tilt")
		return dtiltTime;
	if (move == "forward-smash")
		return fsmashTime;
	if (move == "up-smash")
		return usmashTime;
	if (move == "down-smash")
		return dsmashTime;
	return 0;
}
// < overload for sorting from fastest to slowest, and if they are the same alphabetically
bool operator< (const Fighter& a, const Fighter& b) {
	if (a.getMove() != b.getMove()) {
		return false;
	}
	std::string move = a.getMove();
	if (move == "jab") {
		if (a.getJabTime() < b.getJabTime()) {
			return true;
		} else if (a.getJabTime() == b.getJabTime() && a.getName() < b.getName()) {
			return true;
		}
	} else if (move == "forward-tilt") {
		if (a.getFtiltTime() < b.getFtiltTime())
			return true;
		else if (a.getFtiltTime() == b.getFtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "up-tilt") {
		if (a.getUtiltTime() < b.getUtiltTime())
			return true;
		else if (a.getUtiltTime() == b.getUtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "down-tilt") {
		if (a.getDtiltTime() < b.getDtiltTime())
			return true;
		else if (a.getDtiltTime() == b.getDtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "forward-smash") {
		if (a.getFsmashTime() < b.getFsmashTime())
			return true;
		else if (a.getFsmashTime() == b.getFsmashTime() && a.getName() < b.getName())
			return true;
	} else if (move == "up-smash") {
		if (a.getUsmashTime() < b.getUsmashTime())
			return true;
		else if (a.getUsmashTime() == b.getUsmashTime() && a.getName() < b.getName())
			return true;
	} else if (move == "down-smash") {
		if (a.getDsmashTime() < b.getDsmashTime())
			return true;
		else if (a.getDsmashTime() == b.getDsmashTime() && a.getName() < b.getName())
			return true;
	}
	if (a.getName() < b.getName())
		return true;
	return false;
}
// > overload for sorting slowest first, and if they are the same, then alphabetically
bool operator> (const Fighter& a, const Fighter& b) {
	if (a.getMove() != b.getMove()) {
		return false;
	}
	std::string move = a.getMove();
	if (move == "jab") {
		if (a.getJabTime() > b.getJabTime()) {
			return true;
		} else if (a.getJabTime() == b.getJabTime() && a.getName() < b.getName()) {
			return true;
		}
	} else if (move == "forward-tilt") {
		if (a.getFtiltTime() > b.getFtiltTime())
			return true;
		else if (a.getFtiltTime() == b.getFtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "up-tilt") {
		if (a.getUtiltTime() > b.getUtiltTime())
			return true;
		else if (a.getUtiltTime() == b.getUtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "down-tilt") {
		if (a.getDtiltTime() > b.getDtiltTime())
			return true;
		else if (a.getDtiltTime() == b.getDtiltTime() && a.getName() < b.getName())
			return true;
	} else if (move == "forward-smash") {
		if (a.getFsmashTime() > b.getFsmashTime())
			return true;
		else if (a.getFsmashTime() == b.getFsmashTime() && a.getName() < b.getName())
			return true;
	} else if (move == "up-smash") {
		if (a.getUsmashTime() > b.getUsmashTime())
			return true;
		else if (a.getUsmashTime() == b.getUsmashTime() && a.getName() < b.getName())
			return true;
	} else if (move == "down-smash") {
		if (a.getDsmashTime() > b.getDsmashTime())
			return true;
		else if (a.getDsmashTime() == b.getDsmashTime() && a.getName() < b.getName())
			return true;
	}
	if (a.getName() < b.getName())
		return true;
	return false;
}

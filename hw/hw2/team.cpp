#include <string>
#include "team.h"

Team::Team(std::string aTeamName) {
	teamName = aTeamName;
	win = 0;
	loss = 0;
	tie = 0;
	goal = 0;
	penalty = 0;
	homeWin = 0;
	homeLoss = 0;
	homeTie = 0;
}
std::string Team::getTeamName() const {
	return teamName;
}

int Team::getWin() const {
	return win;
}

int Team::getLoss() const {
	return loss;
}

int Team::getTie() const {
	return tie;
}

float Team::getWinPercent() const {
	if ((Team::getWin() + Team::getLoss() + Team::getTie()) > 0) {
		return ((Team::getWin() + 0.5*Team::getTie()) / (Team::getWin() + Team::getLoss() + Team::getTie()));
	}
	return 0.0;
}

int Team::getGoal() const {
	return goal;
}

int Team::getPenalty() const {
	return penalty;
}

int Team::getHomeWin() const {
	return homeWin;
}

int Team::getHomeLoss() const {
	return homeLoss;
}

int Team::getHomeTie() const {
	return homeTie;
}

float Team::getHomeWinPercent() const {
	if ((Team::getHomeWin() + Team::getHomeLoss() + Team::getHomeTie()) > 0) {
		return ((Team::getHomeWin() + 0.5*Team::getHomeTie()) / (Team::getHomeWin() + Team::getHomeLoss() + Team::getHomeTie()));
	}
	return 0.0;
}

float Team::getHomefieldAdvantage() const {
	if ((Team::getWin() + Team::getTie()) > 0) {
		return (Team::getHomeWinPercent() / getWinPercent());
	}
	return 0.0;
}

void Team::addWin() {
	win += 1;
}

void Team::addLoss() {
	loss += 1;
}

void Team::addTie() {
	tie += 1;
}

void Team::addGoal() {
	goal += 1;
}

void Team::addPenalty() {
	penalty += 1;
}

void Team::addHomeWin() {
	homeWin += 1;
}

void Team::addHomeLoss() {
	homeLoss += 1;
}

void Team::addHomeTie() {
	homeTie += 1;
}

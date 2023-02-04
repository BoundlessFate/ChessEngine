#include <string>
#include "player.h"

Player::Player(std::string aPlayerName, std::string aTeamName) {
	playerName = aPlayerName;
	teamName = aTeamName;
	goal = 0;
	assist = 0;
	penalty = 0;
	homeGoal = 0;
	homeAssist = 0;
	homePenalty = 0;
}

std::string Player::getPlayerName() const {
	return playerName;
}

std::string Player::getTeamName() const {
	return teamName;
}

int Player::getGoal() const {
	return goal;
}

int Player::getAssist() const {
	return assist;
}

int Player::getPenalty() const {
	return penalty;
}

int Player::getHomeGoal() const {
	return homeGoal;
}

int Player::getHomeAssist() const {
	return homeAssist;
}

int Player::getHomePenalty() const {
	return homePenalty;
}
void Player::addGoal() {
	goal += 1;
}

void Player::addAssist() {
	assist += 1;
}

void Player::addPenalty() {
	penalty += 1;
}

void Player::addHomeGoal() {
	homeGoal += 1;
}

void Player::addHomeAssist() {
	homeAssist += 1;
}

void Player::addHomePenalty() {
	homePenalty += 1;
}

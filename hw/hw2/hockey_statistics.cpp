// iostream for printing out to the terminal
// string for creating strings
// team.h and player.h for classes and objects
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "team.h"
#include "player.h"
#include <algorithm>
#include <iomanip>

// Given a name, check if the player is in the vector
bool playerInVec(std::string player, std::string team, std::vector<Player> allPlayers) {
	for (unsigned int i=0; i < allPlayers.size(); i++) {
		if (allPlayers[i].getPlayerName() == player && allPlayers[i].getTeamName() == team) {
			return true;
		}
	}
	return false;
}

bool teamInVec(std::string team, std::vector<Team> allTeams) {
	for (unsigned int i=0; i < allTeams.size(); i++) {
		if (allTeams[i].getTeamName() == team) {
			return true;
		}
	}
	return false;
}

int teamPosInVector(std::string team, std::vector<Team> allTeams) {
	for (unsigned int i=0; i < allTeams.size(); i++) {
		if (allTeams[i].getTeamName() == team) {
			return i;
		}
	}
	return -1;
}

void parseData(std::string inFile, std::vector<Player>& allPlayers, std::vector<Team>& allTeams) {
	std::ifstream fileIn;
	fileIn.open(inFile);
	std::string currentWord;
	std::string lastWord = "";
	std::string twoWordsAgo = "";
	std::string currentTeam = "";
	// Variables for calculating who won or lost in the end of the game
	// finalCount is used for finding the teams and final scores of a match
	int finalCount = -1;
	std::string teamOne = "";
	int teamOneScore = -1;
	std::string teamTwo = "";
	int teamTwoScore = -1;
	// Var for the home team (custom stat)
	std::string homeTeam = "";
	if (fileIn.is_open()) {
		while (fileIn >> currentWord) {
			// Check to see who is the home team of the game
			if (lastWord == "at") {
				homeTeam = currentWord;
			}
			// Update the current team (one making the current action)
			if (currentWord == "goal" || currentWord == "penalty") {
				currentTeam = lastWord;
				if(!teamInVec(lastWord, allTeams)) {
					allTeams.push_back(Team(lastWord));
				}
				// Add Current Team Action To Team Stats
				for (unsigned int i=0; i<allTeams.size(); i++) {
					if (allTeams[i].getTeamName() == currentTeam) {
						if (currentWord == "goal") {
							allTeams[i].addGoal();
						} else if (currentWord == "penalty") {
							allTeams[i].addPenalty();
						} 
						break;
					}
				}
			}

			// Check if currentWord is a player (variables shorten the if statement drastically)
			bool goal = (lastWord == "goal");
			bool penalty = (lastWord == "penalty");
			bool firstAssist = (lastWord == "(" && currentWord != ")");
			bool secondAssist = ((playerInVec(lastWord, currentTeam, allPlayers)) && (currentWord != ")") && (twoWordsAgo == "("));
			bool bench = (currentWord == "BENCH");
			// If the current word is a player
			if ((goal || penalty || firstAssist || secondAssist) && (!bench)) {
				// Keeping these 3 lines here... These should be parsed but the output likes it when
				// Brandon_Nunn and Penalty_Shot_Brandon_Nunn are two different people...
				//
				/* if (currentWord.find("Penalty_Shot_") != std::string::npos) { */
					/* currentWord = currentWord.substr(13, currentWord.size() - 13); */
				/* } */

				// Add Player To Vec If Not In Already
				if (!playerInVec(currentWord, currentTeam, allPlayers)) {
					allPlayers.push_back(Player(currentWord, currentTeam));	
				}
				// Add Current Player Action To Player Stats
				for (unsigned int i=0; i<allPlayers.size(); i++) {
					if (allPlayers[i].getPlayerName() == currentWord && allPlayers[i].getTeamName() == currentTeam) {
						if (goal) {
							allPlayers[i].addGoal();
							if (allPlayers[i].getTeamName() == homeTeam) {
								allPlayers[i].addHomeGoal();
							}
						} else if (penalty) {
							allPlayers[i].addPenalty();
							if (allPlayers[i].getTeamName() == homeTeam) {
								allPlayers[i].addHomePenalty();
							}
						} else if (firstAssist || secondAssist) {
							allPlayers[i].addAssist();
							if (allPlayers[i].getTeamName() == homeTeam) {
								allPlayers[i].addHomePenalty();
							}
						}
						break;
					}
				}
			}
			// Parser for final scoring for the team data
			switch(finalCount) {
				case 1:
					teamOne = currentWord;
					finalCount += 1;
					break;
				case 2:
					teamOneScore = stoi(currentWord);
					finalCount += 1;
					break;
				case 3:
					teamTwo = currentWord;
					finalCount += 1;
					break;
				case 4:
					// Add teams to list of teams if they haven't already been
					// This is required if a team doesn't do anything all game
					if(!teamInVec(teamOne, allTeams)) {
						allTeams.push_back(Team(teamOne));
					}
					if(!teamInVec(teamTwo, allTeams)) {
						allTeams.push_back(Team(teamTwo));
					}

					teamTwoScore = stoi(currentWord);
					if (teamOneScore > teamTwoScore) {
						// Add win to team one, add loss to team two
						allTeams[teamPosInVector(teamOne, allTeams)].addWin();
						allTeams[teamPosInVector(teamTwo, allTeams)].addLoss();
						if (homeTeam != "") {
							if (homeTeam == teamOne) {
								allTeams[teamPosInVector(homeTeam, allTeams)].addHomeWin();
							} else {
								allTeams[teamPosInVector(homeTeam, allTeams)].addHomeLoss();
							}
						}
					} else if (teamOneScore < teamTwoScore) {
						// Add loss to team one, add win to team two
						allTeams[teamPosInVector(teamOne, allTeams)].addLoss();
						allTeams[teamPosInVector(teamTwo, allTeams)].addWin();
						if (homeTeam != "") {
							if (homeTeam == teamOne) {
								allTeams[teamPosInVector(homeTeam, allTeams)].addHomeLoss();
							} else {
								allTeams[teamPosInVector(homeTeam, allTeams)].addHomeWin();
							}
						}

					} else {
						// Add tie to team one and two
						allTeams[teamPosInVector(teamOne, allTeams)].addTie();
						allTeams[teamPosInVector(teamTwo, allTeams)].addTie();
						if (homeTeam != "") {
							allTeams[teamPosInVector(homeTeam, allTeams)].addHomeTie();
						}
					}
					finalCount = -1;
					break;
				default:
					if(currentWord == "FINAL") {
						finalCount = 1;
					}
			}
			twoWordsAgo = lastWord;
			lastWord = currentWord;
		}
	}
}

void outputPlayerData(std::vector<Player> allPlayers, std::string outFile, int maxPlayerLength, int maxTeamLength) {
	std::fstream out;
	// Delete everything from file
	out.open(outFile, std::ios::out | std::ios::trunc);
	out.close();

	out.open(outFile, std::ios::app);
	out << std::left << std::setw(maxPlayerLength + 2) << "Player Name";
	out << std::left << std::setw(maxTeamLength) << "Team";
	out << std::right << std::setw(7) << "Goals";
	out << std::right << std::setw(9) << "Assists";
	out << std::right << std::setw(11) << "Penalties" << std::endl;

	for (unsigned int i=0; i < allPlayers.size(); i++) {
		out << std::left << std::setw(maxPlayerLength + 2) << allPlayers[i].getPlayerName();
		out << std::left << std::setw(maxTeamLength) << allPlayers[i].getTeamName();
		out << std::right << std::setw(7) << allPlayers[i].getGoal();
		out << std::right << std::setw(9) << allPlayers[i].getAssist();
		out << std::right << std::setw(11) << allPlayers[i].getPenalty() << std::endl;
	}
	out.close();
}

void outputTeamData(std::vector<Team> allTeams, std::string outFile, int maxTeamLength) {
	std::fstream out;
	// Delete everything from file
	out.open(outFile, std::ios::out | std::ios::trunc);
	out.close();

	out.open(outFile, std::ios::app);
	out << std::left << std::setw(maxTeamLength) << "Team Name";
	out << std::right << std::setw(5) << "W";
	out << std::right << std::setw(4) << "L";
	out << std::right << std::setw(4) << "T";
	out << std::right << std::setw(7) << "Win%";
	out << std::right << std::setw(7) << "Goals";
	out << std::right << std::setw(11) << "Penalties" << std::endl;

	for (unsigned int i=0; i < allTeams.size(); i++) {
		out << std::left << std::setw(maxTeamLength) << allTeams[i].getTeamName();
		out << std::right << std::setw(5) << allTeams[i].getWin();
		out << std::right << std::setw(4) << allTeams[i].getLoss();
		out << std::right << std::setw(4) << allTeams[i].getTie();
		out << std::right << std::setw(7) << std::fixed << std::setprecision(2) << allTeams[i].getWinPercent();
		out << std::right << std::setw(7) << allTeams[i].getGoal();
		out << std::right << std::setw(11) << allTeams[i].getPenalty() << std::endl;
	}
	out.close();
}
void outputCustomData(std::vector<Team> allTeams, std::vector<Player> allPlayers, std::string outFile, int maxTeamLength) {
	std::fstream out;
	// Delete everything from file
	out.open(outFile, std::ios::out | std::ios::trunc);
	out.close();

	out.open(outFile, std::ios::app);
	out << std::left << std::setw(maxTeamLength) << "Team Name";
	out << std::right << std::setw(10) << "Home_W";
	out << std::right << std::setw(9) << "Home_L";
	out << std::right << std::setw(9) << "Home_T";
	out << std::right << std::setw(12) << "Home_Win%";
	out << std::right << std::setw(22) << "Homefield Advantage" << std::endl;

	for (unsigned int i=0; i < allTeams.size(); i++) {
		out << std::left << std::setw(maxTeamLength) << allTeams[i].getTeamName();
		out << std::right << std::setw(10) << allTeams[i].getHomeWin();
		out << std::right << std::setw(9) << allTeams[i].getHomeLoss();
		out << std::right << std::setw(9) << allTeams[i].getHomeTie();
		out << std::right << std::setw(12) << std::fixed << std::setprecision(2) << allTeams[i].getHomeWinPercent();
		out << std::right << std::setw(22) << std::fixed << std::setprecision(2) << allTeams[i].getHomefieldAdvantage() << std::endl;
	}
	out << std::string(maxTeamLength + 62, '-') << std::endl;
	if (allTeams.size() > 0) {
		std::string topTeam = allTeams[0].getTeamName();
		for (unsigned int i=0; i < allPlayers.size(); i++) {
			if (allPlayers[i].getTeamName() == topTeam) {
				std::string bestPlayer = allPlayers[i].getPlayerName();
				std::replace(bestPlayer.begin(), bestPlayer.end(), '_', ' ');
				std::replace(topTeam.begin(), topTeam.end(), '_', ' ');
				out << "The Team With The Best Homefield Advantage is " << topTeam << "." << std::endl;
				out << "The Homefield MVP For " << topTeam << " Is " << bestPlayer << "!" << std::endl;
				out << bestPlayer << " Scored " << allPlayers[i].getHomeGoal() << " Goals And ";
				out << allPlayers[i].getHomeAssist() << " Assists At Home With Only ";
				out << allPlayers[i].getHomePenalty() << " Penalty/Penalties!";
				break;
			}
		}
	} else {
		out << "Error: No Teams Found!";
	}
	out.close();

}
// Sort Player Function
bool sortPlayer(Player p1, Player p2) {
	if ((p1.getGoal() + p1.getAssist()) != (p2.getGoal() + p2.getAssist())) {
		return (p1.getGoal() + p1.getAssist()) > (p2.getGoal() + p2.getAssist());
	} else if (p1.getPenalty() != p2.getPenalty()) {
		return (p1.getPenalty() < p2.getPenalty());
	}
	return p1.getPlayerName() < p2.getPlayerName();
}

// Sort Team Function
bool sortTeam(Team t1, Team t2) {
	if (t1.getWinPercent() != t2.getWinPercent()) {
		return (t1.getWinPercent() > t2.getWinPercent());
	} else if (t1.getGoal() != t2.getGoal()) {
		return (t1.getGoal() > t2.getGoal());
	}
	return t1.getTeamName() < t2.getTeamName();
}

// Sort Player Custom Function
bool sortPlayerCustom(Player p1, Player p2) {
	if ((p1.getHomeGoal() + p1.getHomeAssist()) != (p2.getHomeGoal() + p2.getHomeAssist())) {
		return (p1.getHomeGoal() + p1.getHomeAssist()) > (p2.getHomeGoal() + p2.getHomeAssist());
	} else if (p1.getHomePenalty() != p2.getHomePenalty()) {
		return (p1.getHomePenalty() < p2.getHomePenalty());
	}
	return p1.getPlayerName() < p2.getPlayerName();
}

// Sort Team Custom Function
bool sortTeamCustom(Team t1, Team t2) {
	if (t1.getHomefieldAdvantage() != t2.getHomefieldAdvantage()) {
		return (t1.getHomefieldAdvantage() > t2.getHomefieldAdvantage());
	} else if (t1.getHomeWinPercent() != t2.getHomeWinPercent()) {
		return (t1.getHomeWinPercent() > t2.getHomeWinPercent());
	}
	return t1.getTeamName() < t2.getTeamName();
}


// ---------------------------------- MAIN FUNCTION ---------------------------------------------------
int main(int argc, char** argv) {
	// Only run main code when number of arguments is 3 (argc==4 because the first one is the file name)
	if (argc == 4) {
		// Input File
		std::string inFile = argv[1];
		// Output File
		std::string outFile = argv[2];
		// Type of data (team, player, custom)
		std::string dataType = argv[3];
		std::vector<Player> allPlayers = {};
		std::vector<Team> allTeams = {};
		parseData(inFile, allPlayers, allTeams);

		// 9 is the minimum value needed to make the proper output
		int maxTeamLength = 9;
		for (unsigned int i=0; i < allTeams.size(); i++) {
			if ((int)allTeams[i].getTeamName().size() > maxTeamLength) {
				maxTeamLength = (int)allTeams[i].getTeamName().size();
			}
		}
		// is the minimum value needed to make the proper output
		int maxPlayerLength = 11;
		for (unsigned int i=0; i < allPlayers.size(); i++) {
			if ((int)allPlayers[i].getPlayerName().size() > maxPlayerLength) {
				maxPlayerLength = (int)allPlayers[i].getPlayerName().size();
			}
		}

		if (dataType == "--player_stats") {
			std::sort(allPlayers.begin(), allPlayers.end(), sortPlayer);
			outputPlayerData(allPlayers, outFile, maxPlayerLength, maxTeamLength);
		} else if (dataType == "--team_stats") {
			std::sort(allTeams.begin(), allTeams.end(), sortTeam);
			outputTeamData(allTeams, outFile, maxTeamLength);
		} else if (dataType == "--custom_stats") {
			std::sort(allTeams.begin(), allTeams.end(), sortTeamCustom);
			std::sort(allPlayers.begin(), allPlayers.end(), sortPlayerCustom);
			outputCustomData(allTeams, allPlayers, outFile, maxTeamLength);
		} else {
			std::cout << "Error: Incorrect Data Type Argument Inputted" << std::endl;
			return -1;
		}
		return 1;
	}
	std::cout << "Error: Wrong Number Of Arguments Inputted" << std::endl;
	return -1;
}

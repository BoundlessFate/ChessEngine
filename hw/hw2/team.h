#include <string>
class Team {
public:
	Team(std::string aTeamName);

	// Accesors
	std::string getTeamName() const;
	int getWin() const;
	int getLoss() const;
	int getTie() const;
	float getWinPercent() const;
	int getGoal() const;
	int getPenalty() const;
	int getHomeWin() const;
	int getHomeLoss() const;
	int getHomeTie() const;
	float getHomeWinPercent() const;
	float getHomefieldAdvantage() const;

	// Modifiers
	void addWin();
	void addLoss();
	void addTie();
	void addGoal();
	void addPenalty();
	void addHomeWin();
	void addHomeLoss();
	void addHomeTie();

	// No Other Member Functions

private:
	std::string teamName;
	int win;
	int loss;
	int tie;
	int goal;
	int penalty;
	int homeWin;
	int homeLoss;
	int homeTie;
};

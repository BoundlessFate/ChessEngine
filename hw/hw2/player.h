#include <string>
class Player {
public:
	Player(std::string aPlayerName, std::string aTeamName);

	// Accesors
	std::string getPlayerName() const;
	std::string getTeamName() const;
	int getGoal() const;
	int getAssist() const;
	int getPenalty() const;
	int getHomeGoal() const;
	int getHomeAssist() const;
	int getHomePenalty() const;

	// Modifiers
	void addGoal();
	void addAssist();
	void addPenalty();
	void addHomeGoal();
	void addHomeAssist();
	void addHomePenalty();

	// No other member functions needed

private:
	std::string playerName;
	std::string teamName;
	int goal;
	int assist;
	int penalty;
	int homeGoal;
	int homeAssist;
	int homePenalty;
};

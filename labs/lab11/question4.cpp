#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
typedef map<string, int> TallyType;
typedef map<int ,set<string>> DataType;
void bestActors(const set<string>& actors, const vector<string>& votes) {
	std::set<std::string>::const_iterator a_itr;
	TallyType tally;
	for (a_itr = actors.begin(); a_itr != actors.end(); a_itr++) {
		tally[*a_itr] = 0;
	}
	for (int i=0; i<votes.size(); i++) {
		tally[votes[i]]++;
	}
	DataType data;
	TallyType::iterator t_itr;
	for (t_itr = tally.begin(); t_itr != tally.end(); t_itr++) {
		data[t_itr->second].insert(t_itr->first);
	}
	DataType::iterator d_itr = --data.end();
	std::set<std::string>::const_iterator s_itr = d_itr->second.begin();
	for(int i=0; i<3; i++){
		std::cout << "Actor #" << i+1 << ": " << *s_itr << endl;
		s_itr++;
		if(s_itr == d_itr->second.end()){
			d_itr--;
			s_itr = d_itr->second.begin();
		}
	}
	d_itr = data.begin(); s_itr = d_itr->second.begin();
	std::cout << "Worst actor: " << *s_itr << std::endl;
}

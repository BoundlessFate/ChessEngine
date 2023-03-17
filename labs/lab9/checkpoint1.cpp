#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
void FindModes(std::string file) {
	std::ifstream fileIn; 
	fileIn.open(file);
	std::string currentWord;
	std::vector<int> allNums;
	std::map<int, int> numAppearances;
	std::map<int,int>::iterator numFind;
	if (fileIn.is_open()) {
		while (fileIn >> currentWord) {
			int currentNum = stoi(currentWord);
			numFind = numAppearances.find(currentNum);
			if (numFind == numAppearances.end()) {
				numAppearances.insert({currentNum,1});
			} else {
				numFind->second++;
			}
		}
	}
	std::vector<int> modes;
	int max = 0;
	for (std::map<int,int>::iterator i=numAppearances.begin(); i != numAppearances.end(); i++) {
		if (i->second > max) {
			max = i->second;
			modes = {};
			modes.push_back(i->first);
		} else if (i->second == max) {
			modes.push_back(i->first);
		}
	}
	std::cout << "The Modes Are:" << std::endl;
	for (unsigned int i=0; i<modes.size(); i++) {
		std::cout << modes[i] << std::endl;
	}
	return;
}
int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Incorrect Number Of Arguments." << std::endl;
	}
	std::string inputFile = argv[1];
	FindModes(inputFile);
	return 1;
}


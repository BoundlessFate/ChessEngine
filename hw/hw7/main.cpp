#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "Fighter.cpp"
//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here

void qAction(char*& outputFile, std::map<std::string, Fighter>& data, std::string& wordOne, std::string& wordTwo) {
	return;
}
void fAction(char*& outputFile, std::map<std::string, Fighter>& data, std::string& wordOne, std::string& wordTwo) {
	return;
}
void sAction(char*& outputFile, std::map<std::string, Fighter>& data, std::string& wordOne, std::string& wordTwo) {
	return;
}
void dAction(char*& outputFile, std::map<std::string, Fighter>& data, std::string& wordOne, std::string& wordTwo) {
	return;
}
std::map<std::string, Fighter> ParseDatabase(char*& inputFileName) {
	std::map<std::string, Fighter> fighterMap;
	std::ifstream inFile;
	inFile.open(inputFileName);
	std::string currentWord;
	std::string name;
	int jab;
	int ftilt;
	int utilt;
	int dtilt;
	int fsmash;
	int usmash; 
	int dsmash;
	bool isCharacter = true;
	unsigned int wordNum = 0;
	if (inFile.is_open()) {
		while(inFile >> currentWord) {
			switch(wordNum) {
				case 0:
					name = currentWord;
					wordNum++;
					break;
				case 1:
					if (isdigit(currentWord[0])) {
						jab = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 2:
					if (isdigit(currentWord[0])) {
						ftilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 3:
					if (isdigit(currentWord[0])) {
						utilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 4:
					if (isdigit(currentWord[0])) {
						dtilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 5:
					if (isdigit(currentWord[0])) {
						fsmash = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 6:
					if (isdigit(currentWord[0])) {
						usmash = stoi(currentWord);	
					} else {
						isCharacter = false;
					}
					wordNum++;
					break;
				case 7:
					if (isdigit(currentWord[0])) {
						dsmash = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					if (isCharacter)
						fighterMap.insert({name,Fighter(jab, ftilt, utilt, dtilt, fsmash, usmash, dsmash)});
					wordNum = 0;
					isCharacter = true;
					break;
				default:
					wordNum = 0;
					isCharacter = true;
					break;
			}
			wordNum++;
		}
	}
	return fighterMap;
}
void ParseInput(char*& inputFile, char*& outputFile, std::map<std::string, Fighter>& data) {
	std::ifstream inFile;
	inFile.open(inputFile);
	std::string currentWord;
	std::string wordOne;
	std::string wordTwo;
	char action;
	unsigned int num;
	if (inFile.is_open()) {
		while(inFile >> currentWord) {
			if (currentWord == "-q") {
				action = 'q';
				num = 0;
			} else if (currentWord == "-f") {
				action = 'f';
				num = 0;
			} else if (currentWord == "-s") {
				action = 's';
				num = 0;
			} else if (currentWord == "-d") {
				action = 'd';
				num = 0;
			} else if (num == 1)
				wordOne = currentWord;
			else if (num == 2) {
				wordTwo = currentWord;
				if (action == 'q')
					qAction(outputFile, data, wordOne, wordTwo);
				else if (action == 'f') 
					fAction(outputFile, data, wordOne, wordTwo);
				else if (action == 's') 
					sAction(outputFile, data, wordOne, wordTwo);
				else if (action == 'd') 
					dAction(outputFile, data, wordOne, wordTwo);
			}
			num++;
		}
	}
	return;
}
int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}
	std::map<std::string, Fighter> data = ParseDatabase(argv[1]);
	ParseInput(argv[2], argv[3], data);
	return 1;
}

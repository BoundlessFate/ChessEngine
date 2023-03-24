// Include statements
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "Fighter.h"
#include <algorithm>
#include <set>
//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};

//Feel free to put forward declarations here
// code to do the -q action
void qAction(char*& outputFile, std::map<std::string, Fighter>& data, std::string& wordOne, std::string& wordTwo) {
	// Create an ofstream for the file to write to
	std::ofstream outFile;
	outFile.open(outputFile, std::ios_base::app);
	// Find the character with that name
	std::map<std::string, Fighter>::iterator character = data.find(wordOne);
	// Check for an invalid
	if (character == data.end()) {
		outFile << "Invalid character name: " << wordOne << std::endl;
		outFile << std::endl;
		outFile.close();
		return;
	}
	// If the file requested for all moves to be outputted
	if (wordTwo == "all") {
		outFile << wordOne << " down-smash: " << (character->second).getDsmashTime() << std::endl;
		outFile << wordOne << " down-tilt: " << (character->second).getDtiltTime() << std::endl;
		outFile << wordOne << " forward-smash: " << (character->second).getFsmashTime() << std::endl;
		outFile << wordOne << " forward-tilt: " << (character->second).getFtiltTime() << std::endl;
		outFile << wordOne << " jab: " << (character->second).getJabTime() << std::endl;
		outFile << wordOne << " up-smash: " << (character->second).getUsmashTime() << std::endl;
		outFile << wordOne << " up-tilt: " << (character->second).getUtiltTime() << std::endl;
		outFile << std::endl;
		return;
	}
	// Find if the move is valid
	bool validMove = false;
	for (unsigned int i=0; i < 7; i++) {
		if (move_names[i] == wordTwo) {
			validMove = true;
		}
	}
	// If the move isnt valid
	if (!validMove) {
		outFile << "Invalid move name: " << wordTwo << std::endl << std::endl;
		return;
	}
	// Output the data for the move from the selected character
	(character->second).setMove(wordTwo);
	outFile << wordOne << " " << wordTwo << ": " << (character->second).GetMoveTime()
		<< std::endl << std::endl;
	// Close out of the file
	outFile.close();
	return;
}
// Code for -f request
void fAction(char*& outputFile, std::map<std::string, Fighter>& data, 
		std::string& wordOne, std::string& wordTwo) {
	// Create ofstream for output file
	std::ofstream outFile;
	outFile.open(outputFile, std::ios_base::app);
	// Check if the moves are valid
	bool validMove = false;
	for (unsigned int i=0; i < 7; i++) {
		if (move_names[i] == wordOne) {
			validMove = true;
		}
	}
	// If not valid, say so in the output file
	if (!validMove) {
		outFile << "Invalid move name: " << wordOne << std::endl << std::endl;
		outFile.close();
		return;
	}
	// Else, go on like normal
	outFile << "-f " << wordOne << " " << wordTwo << std::endl;
	std::set<Fighter> fighterSet;
	// Turn the map into an ordered set
	for (std::map<std::string, Fighter>::iterator i = data.begin(); 
			i != data.end(); i++) {
		(i->second).setMove(wordOne);
		fighterSet.insert(i->second);
	}
	// Loop through the set
	int count = 0;
	for (std::set<Fighter>::iterator i = fighterSet.begin(); 
			i != fighterSet.end(); i++) {
		// Break out if the number requested has been met
		if (count == stoi(wordTwo)) {
			break;
		}
		// output the information for that index in the set
		outFile << i->getName() << " " << i->GetMoveTime() << std::endl;
		count++;
	}
	// Close out of the file
	outFile << std::endl;
	outFile.close();
	return;
}
// Code for -s action
void sAction(char*& outputFile, std::map<std::string, Fighter>& data,
		std::string& wordOne, std::string& wordTwo) {
	// Create ofstream for output file
	std::ofstream outFile;
	outFile.open(outputFile, std::ios_base::app);
	// Check if the move selected is valid
	bool validMove = false;
	for (unsigned int i=0; i < 7; i++) {
		if (move_names[i] == wordOne) {
			validMove = true;
		}
	}
	// If the move is invalid, say so
	if (!validMove) {
		outFile << "Invalid move name: " << wordOne << std::endl 
			<< std::endl;
		return;
	}
	// else, print normally
	outFile << "-s " << wordOne << " " << wordTwo << std::endl;
	std::set<Fighter, std::greater<Fighter>> fighterSet;
	// Put the map into a sorted sort from largest to smallest
	for (std::map<std::string, Fighter>::iterator i = data.begin();
			i != data.end(); i++) {
		(i->second).setMove(wordOne);
		fighterSet.insert(i->second);
	}
	int count = 0;
	// Loop through the set
	for (std::set<Fighter>::iterator i = fighterSet.begin(); 
			i != fighterSet.end(); i++) {
		// Break out if enough have been printed
		if (count == stoi(wordTwo)) {
			break;
		}
		// Print the index's data
		outFile << i->getName() << " " << i->GetMoveTime() << std::endl;
		count++;
	}
	outFile << std::endl;
	// Close out of the file
	outFile.close();
	return;
}
// Code for -d action
void dAction(char*& outputFile, std::map<std::string, Fighter>& data, 
		std::string& wordOne, std::string& wordTwo) {
	// Create an ofstream for the output file
	std::ofstream outFile;
	outFile.open(outputFile, std::ios_base::app);
	// Check if it is a valid move
	bool validMove = false;
	for (unsigned int i=0; i < 7; i++) {
		if (move_names[i] == wordOne) {
			validMove = true;
		}
	}
	// If not valid move, say so
	if (!validMove) {
		outFile << "Invalid move name: " << wordOne << std::endl << std::endl;
		return;
	}
	// else, continue like normal
	outFile << "-d " << wordOne << " " << wordTwo << std::endl;
	std::set<Fighter> fighterSet;
	// Insert the map into a set from lowest to largest
	for (std::map<std::string, Fighter>::iterator i = data.begin(); 
			i != data.end(); i++) {
		(i->second).setMove(wordOne);
		fighterSet.insert(i->second);
	}
	// iterate through the set, and print out every index with the requested number
	bool foundNum = false;
	for (std::set<Fighter>::iterator i = fighterSet.begin(); 
			i != fighterSet.end(); i++) {
		if (i->GetMoveTime() == stoi(wordTwo)) {
			outFile << i->getName() << std::endl;
		}
		if (foundNum && i->GetMoveTime() != stoi(wordTwo))
			break;
	}
	outFile << std::endl;
	outFile.close();
	return;
}
// Parse through the database of fighter data
std::map<std::string, Fighter> ParseDatabase(char*& inputFileName) {
	// Create a map of strings and fighters
	std::map<std::string, Fighter> fighterMap;
	// Open up the database file
	std::ifstream inFile;
	inFile.open(inputFileName);
	// Create initial variables
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
	// Loop through every word
	if (inFile.is_open()) {
		while(inFile >> currentWord) {
			// Go through each word on the line, settings different variables
			switch(wordNum) {
				case 0:
					name = currentWord;
					break;
				case 1:
					if (isdigit(currentWord[0])) {
						jab = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					break;
				case 2:
					if (isdigit(currentWord[0])) {
						ftilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					break;
				case 3:
					if (isdigit(currentWord[0])) {
						utilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					break;
				case 4:
					if (isdigit(currentWord[0])) {
						dtilt = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					break;
				case 5:
					if (isdigit(currentWord[0])) {
						fsmash = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					break;
				case 6:
					if (isdigit(currentWord[0])) {
						usmash = stoi(currentWord);	
					} else {
						isCharacter = false;
					}
					break;
				case 7:
					if (isdigit(currentWord[0])) {
						dsmash = stoi(currentWord);
					} else {
						isCharacter = false;
					}
					// If it is a character (not first line)
					if (isCharacter)
						// Insert the data into the map
						fighterMap.insert({name,Fighter(name, jab, ftilt, 
									utilt, dtilt, fsmash, usmash, dsmash)});
					wordNum = -1;
					isCharacter = true;
					break;
				default:
					wordNum = -1;
					isCharacter = true;
					break;
			}
			wordNum++;
		}
	}
	// Return the map
	return fighterMap;
}
// Parses the lines from the input file
void ParseInput(char*& inputFile, char*& outputFile, 
		std::map<std::string, Fighter>& data) {
	// Create ifstream for input file
	std::ifstream inFile;
	inFile.open(inputFile);
	// Create initial variables
	std::string currentWord;
	std::string wordOne;
	std::string wordTwo;
	char action;
	unsigned int num;
	// Loop through each word
	if (inFile.is_open()) {
		while(inFile >> currentWord) {
			// Get the current action
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
				// Get wordOne
				wordOne = currentWord;
			else if (num == 2) {
				// Get wordTwo
				wordTwo = currentWord;
				// Call the function basedo on the action, wordOne, and wordTwo
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
// Main code that runs at the start of the program
int main(int argc, char** argv){
	// Check if the proper number of arguments is enttered
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << 
			" [database file] [input file] [output file]" << std::endl;
		return -1;
	}
	// Check if the database can be opened
	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << 
			" for reading." << std::endl;
	}
	// Check if the input file can be opened
	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << 
			" for reading." << std::endl;
	}
	// Check if the output file can be opened
	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] 
			<< " for writing." << std::endl;
	}
	// Call ParseDatabase
	std::map<std::string, Fighter> data = ParseDatabase(argv[1]);
	// Call ParseInput with the map
	ParseInput(argv[2], argv[3], data);
	return 1;
}

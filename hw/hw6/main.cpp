#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
void CollectData(std::string inputFile, std::vector<std::vector<char>>& grid, std::vector<std::string>& inWords, std::vector<std::string>& outWords) {
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string previousWord;
	unsigned int sizeBool = true;
	unsigned int length, width;
	if (fileIn.is_open()) {
		while (fileIn >> currentWord) {
			bool isNumber = true;
			for (unsigned int i=0; i<currentWord.size(); i++) {
				if (!isdigit(currentWord[i])) {
					isNumber = false;
					break;
				}
			}
			if (isNumber) {
				if (sizeBool) {
					width = stoi(currentWord);
					sizeBool = false;
				} else {
					length = stoi(currentWord);
					for (unsigned int i=0; i< length; i++) {
						std::vector<char> row;
						for (unsigned int j=0; j < width; j++) {
							row.push_back('*');
						}
						grid.push_back(row);
					}
				}
			} else if (previousWord == "+") {
				inWords.push_back(currentWord);
			} else if (previousWord == "-") {
				outWords.push_back(currentWord);
			}
			previousWord = currentWord;
		}
	}
	return;
}
bool addToDirection(unsigned int direction, int x, int y, std::vector<std::vector<char>>& grid, std::string word) {

	// If all letters can be added properly, return true
	if (word.size() == 0) {
		return true;
	}
	// If it went out of bounds, return false
	if (x < 0 || y < 0 || y >= (int)grid.size() || x >= (int)grid[y].size()) {
		return false;
	}
	bool wordWorks = true;
	// If the current space is valid
	if (grid[y][x] == '*' || grid[y][x] == word[0]) {
		char tempLetter = grid[y][x];
		grid[y][x] = word[0];
		word = word.substr(1);
		if (direction == 0) {
			wordWorks = addToDirection(direction, x, y-1, grid, word);
		} else if (direction == 1) {
			wordWorks = addToDirection(direction, x+1, y-1, grid, word); 
		} else if (direction == 2) {
			wordWorks = addToDirection(direction, x+1, y, grid, word); 
		} else if (direction == 3) {
			wordWorks = addToDirection(direction, x+1, y+1, grid, word); 
		} else if (direction == 4) {
			wordWorks = addToDirection(direction, x, y+1, grid, word); 
		} else if (direction == 5) {
			wordWorks = addToDirection(direction, x-1, y+1, grid, word); 
		} else if (direction == 6) {
			wordWorks = addToDirection(direction, x-1, y, grid, word); 
		} else if (direction == 7) {
			wordWorks = addToDirection(direction, x-1, y-1, grid, word); 
		}
		if (!wordWorks) {
			grid[y][x] = tempLetter;
		}
	} else {
		return false;
	}
	return wordWorks;
}
bool CheckDirection(unsigned int direction, int x, int y, std::vector<std::vector<char>>& grid, std::string word) {
	// If all letters can be added properly, return true
	if (word.size() == 0) {
		return true;
	}
	// If it went out of bounds, return false
	if (x < 0 || y < 0 || y >= (int)grid.size() || x >= (int)grid[y].size()) {
		return false;
	}
	bool wordWorks = true;
	// If the current space is valid
	if (grid[y][x] == word[0]) {
		word = word.substr(1);
		if (direction == 0) {
			wordWorks = CheckDirection(direction, x, y-1, grid, word);
		} else if (direction == 1) {
			wordWorks = CheckDirection(direction, x+1, y-1, grid, word); 
		} else if (direction == 2) {
			wordWorks = CheckDirection(direction, x+1, y, grid, word); 
		} else if (direction == 3) {
			wordWorks = CheckDirection(direction, x+1, y+1, grid, word); 
		} else if (direction == 4) {
			wordWorks = CheckDirection(direction, x, y+1, grid, word); 
		} else if (direction == 5) {
			wordWorks = CheckDirection(direction, x-1, y+1, grid, word); 
		} else if (direction == 6) {
			wordWorks = CheckDirection(direction, x-1, y, grid, word); 
		} else if (direction == 7) {
			wordWorks = CheckDirection(direction, x-1, y-1, grid, word); 
		}
	} else {
		return false;
	}
	return wordWorks;
}

void FindSolution(std::vector<std::vector<char>> grid, std::vector<std::string> words, std::vector<std::vector<std::vector<char>>>& allSolutions) {
	if (words.size() == 0) {
		allSolutions.push_back(grid);
		return;
	}
	for (int j=0; j<(int)grid.size(); j++) {
		for (int k=0; k<(int)grid[j].size(); k++) {
			for (unsigned int l=0; l<8; l++) {
				std::vector<std::vector<char>> tempGrid = grid;
				if (addToDirection(l, k, j, tempGrid, words[0])) {
					std::vector<std::string> tempWords = words;
					tempWords.erase(tempWords.begin());
					FindSolution(tempGrid, tempWords, allSolutions);
				}
			}
		}
	}
	return;
}
void CheckSolutions(std::vector<std::vector<std::vector<char>>>& allSolutions, std::vector<std::string> words) {
	std::vector<std::vector<std::vector<char>>> newSolutions;
	if (words.size() == 0) {
		return;
	}
	for (int i=0; i<(int)allSolutions.size(); i++) {
		bool foundIncorrect = false;
		for (int j=0; j<(int)allSolutions[i].size(); j++) {
			for (int k=0; k<(int)allSolutions[i][j].size(); k++) {
				for (unsigned int l=0; l<8; l++) {
					for (int m=0; m<(int)words.size(); m++) {
						if (CheckDirection(l, k, j, allSolutions[i], words[m])) {
							foundIncorrect = true;
							break;
						}
					}
					if (foundIncorrect)
						break;
				}
				if (foundIncorrect)
					break;
			}
			if (foundIncorrect)
				break;
		}
		if (!foundIncorrect) {
			newSolutions.push_back(allSolutions[i]);
		}
	}
	allSolutions = newSolutions;
	return;
}
void DeleteDuplicates(std::vector<std::vector<std::vector<char>>>& allSolutions) {
	std::vector<std::string> allUniqueSolutionStrings;
	std::vector<std::vector<std::vector<char>>> uniqueSolutions;
	for (int i=0; i<(int)allSolutions.size(); i++) {
		std::string currentSolutionString = "";
		for (int j=0; j<(int)allSolutions[i].size(); j++) {
			for (int k=0; k<(int)allSolutions[i][j].size(); k++) {
				currentSolutionString += allSolutions[i][j][k];
			}
		}
		bool unique = true;
		for (int j=0; j<(int)allUniqueSolutionStrings.size(); j++) {
			if (currentSolutionString == allUniqueSolutionStrings[j]) {
				unique = false;
				break;
			}
		}
		if (unique) {
			allUniqueSolutionStrings.push_back(currentSolutionString);
			uniqueSolutions.push_back(allSolutions[i]);
		}
	}
	allSolutions = uniqueSolutions;
	return;
}
void FillSolution(std::vector<std::vector<char>> grid, std::vector<std::vector<std::vector<char>>>& solutionVec, std::vector<char> letters) {
	bool solution = true;
	for (unsigned int i=0; i<grid.size(); i++) {
		for (unsigned int j=0; j<grid[i].size(); j++) {
			if (grid[i][j] == '*') {
				for (unsigned int k=0; k<letters.size(); k++) {
					std::vector<std::vector<char>> tempGrid = grid;
					tempGrid[i][j] = letters[k];
					FillSolution(tempGrid, solutionVec, letters);
				}
				solution = false;
			}
		}
	}
	if (solution)
		solutionVec.push_back(grid);
}
void FillSolutionHandler(std::vector<std::vector<std::vector<char>>>& allSolutions, std::vector<std::string> words) {
	std::vector<char> letters = {'a','b','c','d','e','f','g','h','i','j','k','l',
		'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for (unsigned int i=0; i<words.size(); i++) {
		if (words[i].size() == 1) {
			for (unsigned int j=0; j<letters.size(); j++) {
				if (words[i][0] == letters[j]) {
					letters.erase(letters.begin() + j);
				}
			}
		}
	}
	std::vector<std::vector<std::vector<char>>> newSolutions;
	for (unsigned int i=0; i<allSolutions.size(); i++) {
		FillSolution(allSolutions[i], newSolutions, letters);
	}
	allSolutions = newSolutions;
	return;
}
bool sortBySize(std::string a, std::string b) {
	return a.size() > b.size();
}
// ----------------------- CODE STARTS RUNNING HERE ------------------------------
int main(int argc, char** argv) {
	if (argc == 4) {
		std::string inputFile = argv[1];
		std::string outputFile = argv[2];
		std::string solutionType = argv[3];
		std::vector<std::vector<char>> grid;
		std::vector<std::string> inWords, outWords;
		CollectData(inputFile, grid, inWords, outWords);
		std::cout << "Sorting Words By Length..." << std::endl;
		std::sort(inWords.begin(), inWords.end(), sortBySize);
		std::sort(outWords.begin(), outWords.end(), sortBySize);
		std::cout << "-------------------------------" << std::endl;
		std::cout << "Grid:" << std::endl;
		for (unsigned int i=0; i< grid.size(); i++) {
			for (unsigned int j=0; j < grid[i].size(); j++) {
				std::cout << grid[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << "inWords:";
		for (unsigned int i = 0; i < inWords.size(); i++) {
			std::cout << " " << inWords[i];
		}
		std::cout << std::endl;
		std::cout << "outWords:";
		for (unsigned int i = 0; i < outWords.size(); i++) {
			std::cout << " " << outWords[i];
		}
		std::cout << std::endl;
		std::cout << "-------------------------------" << std::endl;
		std::vector<std::vector<std::vector<char>>> allSolutions;
		std::cout << "Finding Solutions..." << std::endl;
		FindSolution(grid, inWords, allSolutions);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		std::cout << "Deleting Duplicate Solutions..." << std::endl;
		DeleteDuplicates(allSolutions);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		std::cout << "Checking For Bad Solutions..." << std::endl;
		CheckSolutions(allSolutions, outWords);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		std::cout << "Filling Grid..." << std::endl;
		FillSolutionHandler(allSolutions, outWords);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		std::cout << "Deleting Duplicate Solutions..." << std::endl;
		DeleteDuplicates(allSolutions);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		std::cout << "Checking For Bad Solutions..." << std::endl;
		CheckSolutions(allSolutions, outWords);
		std::cout << allSolutions.size() << " Solutions." << std::endl;
		/* for (unsigned int i=0; i<allSolutions.size(); i++) { */
		/* 	for (unsigned int j=0; j<allSolutions[i].size(); j++) { */
		/* 		for (unsigned int k=0; k<allSolutions[i][j].size(); k++) { */
		/* 			std::cout << allSolutions[i][j][k]; */
		/* 		} */
		/* 		std::cout << std::endl; */
		/* 	} */
		/* 	std::cout << std::endl; */
		/* } */
	} else {
		std::cerr << "Error: Incorrect Number Of Arguments Entered." << std::endl;
	}
}

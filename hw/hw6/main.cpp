#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
void FindSolution(std::vector<std::vector<char>> grid, std::vector<std::string> words) {

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
	} else {
		std::cerr << "Error: Incorrect Number Of Arguments Entered." << std::endl;
	}
}

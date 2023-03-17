#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
// This function parses data from the input file
// and returns it to the proper variables inputted
void CollectData(std::string inputFile, std::vector<std::vector<char>>& grid,
		std::vector<std::string>& inWords, std::vector<std::string>& outWords) {
	// Create a file reader
	std::ifstream fileIn;
	fileIn.open(inputFile);
	std::string currentWord;
	std::string previousWord;
	// Boolean is true if talking about rows and false about columns
	unsigned int sizeBool = true;
	// Create a high up length and width variable
	unsigned int length, width;
	// Loop through every word
	if (fileIn.is_open()) {
		while (fileIn >> currentWord) {
			// Check if the worwd is a number
			bool isNumber = true;
			for (unsigned int i=0; i<currentWord.size(); i++) {
				if (!isdigit(currentWord[i])) {
					isNumber = false;
					break;
				}
			}
			// If the word is a number
			if (isNumber) {
				// If it is referring to the row
				if (sizeBool) {
					// Set width stats
					width = stoi(currentWord);
					sizeBool = false;
				// Else it is referring columns
				} else {
					// Set length stats
					length = stoi(currentWord);
					// Create the grid using the variables
					for (unsigned int i=0; i< length; i++) {
						std::vector<char> row;
						for (unsigned int j=0; j < width; j++) {
							row.push_back('*');
						}
						grid.push_back(row);
					}
				}
			// If the word needs to be included in the grid
			} else if (previousWord == "+") {
				// Add the word to to the inWords vector
				inWords.push_back(currentWord);
			// If the word needs to be excluded from the grid
			} else if (previousWord == "-") {
				// Add the word to the outWords vector
				outWords.push_back(currentWord);
			}
			previousWord = currentWord;
		}
	}
	return;
}
// Recursively add a word to a direction, and remove if it doesnt fit
// Return if the word did or did not work
bool addToDirection(unsigned int direction, int x, int y, std::vector<std::vector<char>>& grid, std::string word) {
	// If the word has 0 size, return true
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
		// Get the letter already there
		char tempLetter = grid[y][x];
		// Set the current grid spot to the first letter
		grid[y][x] = word[0];
		// Delete the first letter from the word
		word = word.substr(1);
		// Recurse in the correct direction
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
		// If the word doesn't work (recursion failed)
		if (!wordWorks) {
			// Reset the current spot to its previous value
			grid[y][x] = tempLetter;
		}
	// Return false if the spot can't be moved to
	} else {
		return false;
	}
	// Return wordWorks at the highest level of recursion
	return wordWorks;
}
// Very similar to AddToDirection
// Checks if a word is in a direction, but doesn't add anything
bool CheckDirection(unsigned int direction, int x, int y, 
		std::vector<std::vector<char>>& grid, std::string word) {
	// If word size is 0, return true
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
		// Delete the first letter
		word = word.substr(1);
		// Recurse in the proper direction
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
	// If the word isn't in the direction, return true
	} else {
		return false;
	}
	// Return wordWorks at the highest level of recursion
	return wordWorks;
}
// Finds all solutions for the grid size and inWords
void FindSolution(std::vector<std::vector<char>> grid, 
		std::vector<std::string> words, 
		std::vector<std::vector<std::vector<char>>>& allSolutions) {
	// If there are no words, then the grid is valid
	if (words.size() == 0) {
		allSolutions.push_back(grid);
		return;
	}
	// Loop through all spaces in the grid
	for (int j=0; j<(int)grid.size(); j++) {
		for (int k=0; k<(int)grid[j].size(); k++) {
			// Loop through all 8 direcetions
			for (unsigned int l=0; l<8; l++) {
				// Get the current grid as a new grid
				std::vector<std::vector<char>> tempGrid = grid;
				// Check addToDirection with the new grid and the first word
				if (addToDirection(l, k, j, tempGrid, words[0])) {
					// Recurse with the first word deleted from a temp list
					std::vector<std::string> tempWords = words;
					tempWords.erase(tempWords.begin());
					FindSolution(tempGrid, tempWords, allSolutions);
				}
			}
		}
	}
	return;
}
// Checks if a solution is valid with outWords
void CheckSolutions(std::vector<std::vector<std::vector<char>>>& allSolutions,
		std::vector<std::string> words) {
	// Create new vector for valid solutions
	std::vector<std::vector<std::vector<char>>> newSolutions;
	// Return if there are no words in the vector
	if (words.size() == 0) {
		return;
	}
	// Loop through all solutions
	for (int i=0; i<(int)allSolutions.size(); i++) {
		// Bool for if the solution is incorrect
		bool foundIncorrect = false;
		// Loop through all spacce in the grid
		for (int j=0; j<(int)allSolutions[i].size(); j++) {
			for (int k=0; k<(int)allSolutions[i][j].size(); k++) {
				// Loop through all 8 directions
				for (unsigned int l=0; l<8; l++) {
					// Loop through all forbidden words
					for (int m=0; m<(int)words.size(); m++) {
						// If the forbidden word is in that direction
						if (CheckDirection(l, k, j, allSolutions[i], words[m])) {
							// Then the solution is incorrect
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
		// If the solution is correct, add to new vector
		if (!foundIncorrect) {
			newSolutions.push_back(allSolutions[i]);
		}
	}
	// Set solution vector to new vector
	allSolutions = newSolutions;
	return;
}
// Check and delete all duplicate solutions in the case of palendromes
void DeleteDuplicates(std::vector<std::vector<std::vector<char>>>& allSolutions) {
	// Create a vector of strings
	std::vector<std::string> allUniqueSolutionStrings;
	// Create a new vector of grids
	std::vector<std::vector<std::vector<char>>> uniqueSolutions;
	// Loop through all solutions
	for (int i=0; i<(int)allSolutions.size(); i++) {
		// Convert the solution into a string
		std::string currentSolutionString = "";
		for (int j=0; j<(int)allSolutions[i].size(); j++) {
			for (int k=0; k<(int)allSolutions[i][j].size(); k++) {
				currentSolutionString += allSolutions[i][j][k];
			}
		}
		// Check if the solution string is unique (isnt in the vector of string already)
		bool unique = true;
		for (int j=0; j<(int)allUniqueSolutionStrings.size(); j++) {
			if (currentSolutionString == allUniqueSolutionStrings[j]) {
				unique = false;
				break;
			}
		}
		// If it is new, add it to the 2 new vectors
		if (unique) {
			allUniqueSolutionStrings.push_back(currentSolutionString);
			uniqueSolutions.push_back(allSolutions[i]);
		}
	}
	// Set solution vector equal to new vector
	allSolutions = uniqueSolutions;
	return;
}
// Recursively fill a solution with letters in it's empty spots
void FillSolution(std::vector<std::vector<char>> grid, 
		std::vector<std::vector<std::vector<char>>>& solutionVec, 
		std::vector<char> letters) {
	// Boolean to see if the grid is all full
	bool solution = true;
	// Loop through all spaces
	for (unsigned int i=0; i<grid.size(); i++) {
		for (unsigned int j=0; j<grid[i].size(); j++) {
			// If the spot is a * (empty spot)
			if (grid[i][j] == '*') {
				// Go through every available letter and recurse 
				// with that new letter in place
				for (unsigned int k=0; k<letters.size(); k++) {
					std::vector<std::vector<char>> tempGrid = grid;
					tempGrid[i][j] = letters[k];
					FillSolution(tempGrid, solutionVec, letters);
				}
				// Set this grid as not being a true solution
				solution = false;
			}
		}
	}
	// If this grid is a true solution, add it to the vector
	if (solution)
		solutionVec.push_back(grid);
}
// Helper function for FillSolution
void FillSolutionHandler(std::vector<std::vector<std::vector<char>>>& allSolutions, 
		std::vector<std::string> words) {
	// Vector of the alphabet
	std::vector<char> letters = {'a','b','c','d','e','f','g','h','i','j','k','l',
		'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	// Loop through all outWords
	for (unsigned int i=0; i<words.size(); i++) {
		// If the word size is 1
		if (words[i].size() == 1) {
			// Remove it from the vector of letters to be recursed through
			for (unsigned int j=0; j<letters.size(); j++) {
				if (words[i][0] == letters[j]) {
					letters.erase(letters.begin() + j);
				}
			}
		}
	}
	// Create a vector to house the new solutions
	std::vector<std::vector<std::vector<char>>> newSolutions;
	// Loop through all solutions
	for (unsigned int i=0; i<allSolutions.size(); i++) {
		// Fill the solutions
		FillSolution(allSolutions[i], newSolutions, letters);
	}
	// Set the solution vector to the new vector
	allSolutions = newSolutions;
	return;
}
// Outputs the required information to a file
void OutputToFile(const  std::vector<std::vector<std::vector<char>>>& allSolutions,
		const std::string& outputFile, const std::string& solutionType) {
	// Delete all information previously in the file
	std::ofstream outFile;
	outFile.open(outputFile, std::ofstream::out | std::ofstream::trunc);
	outFile.close();
	// Open the file in append mode
	outFile.open(outputFile, std::ios_base::app);
	// If there are no solutions
	if (allSolutions.size() == 0) {
		outFile << "No solutions found.";
	// If all_solutions was selected
	} else if (solutionType == "all_solutions") {
		// Iterate through, and output all solutions to the file
		outFile << allSolutions.size() << " solution(s)" << std::endl;
		for (unsigned int i=0; i < allSolutions.size(); i++) {
			outFile << "Board:" << std::endl;
			for (unsigned int j=0; j<allSolutions[i].size(); j++) {
				outFile << "  ";
				for (unsigned int k=0; k<allSolutions[i][j].size(); k++) {
					outFile << allSolutions[i][j][k];
				}
				outFile << std::endl;
			}
		}
	// If one_solution was selected
	} else if (solutionType == "one_solution") {
		// Output the first solution that was found in the vector to the file
		outFile << "Board:" << std::endl;
		for (unsigned int i=0; i<allSolutions[0].size(); i++) {
			outFile << "  ";
			for (unsigned int j=0; j<allSolutions[0][i].size(); j++) {
				outFile << allSolutions[0][i][j];
			}
			outFile << std::endl;
		}
	}
	// Close the file
	outFile.close();
	return;
}
// Custom sort by size function, to sort by the largest word size first
bool sortBySize(std::string a, std::string b) {
	return a.size() > b.size();
}
// ----------------------- CODE STARTS RUNNING HERE ------------------------------
int main(int argc, char** argv) {
	// If 4 arguments were selected
	if (argc == 4) {
		// Variables to hold the arguments
		std::string inputFile = argv[1];
		std::string outputFile = argv[2];
		std::string solutionType = argv[3];
		// Variable to hold the empty grid later on
		std::vector<std::vector<char>> grid;
		std::vector<std::string> inWords, outWords;
		// Collect data from the input file
		CollectData(inputFile, grid, inWords, outWords);
		// Sort inWords and outWords (one of my optimizations)
		std::sort(inWords.begin(), inWords.end(), sortBySize);
		std::sort(outWords.begin(), outWords.end(), sortBySize);
		// Vector to hold the solutions in
		std::vector<std::vector<std::vector<char>>> allSolutions;
		// Find the solutions
		FindSolution(grid, inWords, allSolutions);
		// Check the solutions with the outWords
		CheckSolutions(allSolutions, outWords);
		// Fill the remaining solutions empty spots with characters
		FillSolutionHandler(allSolutions, outWords);
		// Delete the duplicate words in case of palendromes
		DeleteDuplicates(allSolutions);
		// Check the solutions for forbidden words created from the FillSolutions
		CheckSolutions(allSolutions, outWords);
		// Output the solutions to the outputFile
		OutputToFile(allSolutions, outputFile, solutionType);
	} else {
		// Error message for incorrect number of arguments
		std::cerr << "Error: Incorrect Number Of Arguments Entered." << std::endl;
	}
}

// Include iostream (for errors)
// string.h (for using strings)
// fstream for file I/O
// vector for vectors
// math.h for ceil function in the Full_Justify() method
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

// Gets the max size of a string inside a vector
int maxSize(std::vector<std::string> vecIn) {
	int max = 0;
	for (int i=0; i < (int)vecIn.size(); i++) {
		if ((int)vecIn[i].size() > max) {
			max = (int)vecIn[i].size();
		}
	}
	return max;
}
std::vector<std::string> Hyphenate(std::vector<std::string> vecIn, int length) {
	std::vector<std::string> vecOut = {};
	while(true) {
		for (int i = 0; i < (int)vecIn.size(); i++) {
			if ((int)vecIn[i].size() > length) {
				vecOut.push_back(vecIn[i].substr(0, length - 1) + "-");
				vecOut.push_back(vecIn[i].substr(length - 1));
			} else {
				vecOut.push_back(vecIn[i]);
			}
		}
		// Break out of the loop if nothing else needs to be hyphenated
		if (maxSize(vecOut) <= length) {
			break;
		}
		// S
		vecIn = vecOut;
		vecOut = {};
	}
	return vecOut;
}

// Returns a vector of vector of strings that finds the number of words that can fit on each line in the box
std::vector<std::vector<std::string>> FormulateLines(std::string inFile, int length, bool tri) {
	std::ifstream fileIn; 
	fileIn.open(inFile);		
	std::vector<std::string> fileInContents;
	std::string nextWord;
	if (fileIn.is_open()) {
		while (fileIn >> nextWord) {
			fileInContents.push_back(nextWord);
			nextWord.clear();
		}
	}
	// Hyphenate long words (break them into smaller words with a hyphen at the end)
	fileInContents = Hyphenate(fileInContents, length);
	int numWords = fileInContents.size();

	// Section off lines as a vector of vector of strings (each line gets a vector, and another vector encapsulates all the vectors)
	std::vector<std::vector<std::string>> boxLines;
	// Create first blank line in the box
	boxLines.push_back({});
	int currentLineLength = 0;
	int currentLine = 0;
	std::string currentValue = "";
	for (int i=0; i < numWords; i++) {
		// If the current line has nothing on it, the next word will always be added to this line
		if ((int)boxLines[currentLine].size() == 0) {
			boxLines[currentLine].push_back(fileInContents[i]);
			currentLineLength += fileInContents[i].length();
			// Check if the next word can fit on the current line
		} else if ((length - currentLineLength) >= (int)fileInContents[i].length() + 1) {
			// Add space to previous word if possible
			if (!((int)boxLines[currentLine].size() == 0)) {
				// Create reference to previous value of last word
				boxLines[currentLine].back() = boxLines[currentLine].back() + " ";
				currentLineLength += 1;
			}

			boxLines[currentLine].push_back(fileInContents[i]);
			currentLineLength += fileInContents[i].length();
		} else {
			currentLine += 1;
			boxLines.push_back({fileInContents[i]});
			currentLineLength = fileInContents[i].length();
		}
	}
	return boxLines;
}
// Consolidates duplicate code from FlushLeft and FlushRight functions (they only needed one line changed between the two types)
// Stands for Flush Left And Right Shortener
void FLARS(std::vector<std::vector<std::string>> boxLines, std::string outFile, int length, std::string formatType) {
	std::fstream out;
	out.open(outFile, std::ios::app);
	out << std::string(length + 4, '-') << std::endl;
	std::string line = "";
	for (int i=0; i < (int)boxLines.size(); i++) {
		int lineCharCount = 0;
		line = "";
		for (int j=0; j < (int)boxLines[i].size(); j++) {
			lineCharCount += (int)boxLines[i][j].length();
			line = line + boxLines[i][j];
		}
		// Handle The Different Format Types
		// Flush Left
		if (formatType == "flush_left") {
			line = line + std::string(length - lineCharCount, ' ');
		} else if (formatType == "flush_right") {
			line = std::string(length - lineCharCount, ' ') + line;
		} else {
			std::cout << "Error: Bad Justification Argument. This Should Never Be Output.";
		}
		line = line + " |";
		line = "| " + line;
		out << line << std::endl;
	} 
	line = std::string(length + 4, '-');
	out << line << std::endl;
	out.close();
}
// Only reason this is now added to the FLARS method above is because this requires more changes to the line spacing than FLARS did
// Deals with full justify
void Full_Justify(std::vector<std::vector<std::string>> boxLines, std::string outFile, int length) {
	std::fstream out;
	out.open(outFile, std::ios::app);
	out << std::string(length + 4, '-') << std::endl;
	std::string line = "";
	for (int i=0; i < (int)boxLines.size(); i++) {
		// Get total num of spaces to be added
		int lineCharCount = 0;
		for (int j=0; j < (int)boxLines[i].size(); j++) {
			lineCharCount += (int)boxLines[i][j].length();
		}
		int gapsLeft = boxLines[i].size() - 1;
		// Catch the case where there is only one word on the line
		int spacesLeft = length - lineCharCount;
		if (gapsLeft == 0) {
			boxLines[i][0] = boxLines[i][0] + std::string(ceil((float)spacesLeft), ' ');
		}
		// Add spaces evenly, adding additional ones to the leftmost ones if necessary
		for (int j=0; j < (int)boxLines[i].size() - 1; j++) {
			boxLines[i][j] = boxLines[i][j] + std::string(ceil((float)spacesLeft/gapsLeft), ' ');
			spacesLeft -= ceil((float)spacesLeft/gapsLeft);
			gapsLeft -= 1;
		}
		// Print out these vectors as if there was no justify applied
		line = "";
		for (int j=0; j < (int)boxLines[i].size(); j++) {
			lineCharCount += (int)boxLines[i][j].length();
			line = line + boxLines[i][j];
		}
		line = line + " |";
		line = "| " + line;
		out << line << std::endl;
	} 
	line = std::string(length + 4, '-');
	out << line << std::endl;
	out.close();
}
// argc is the number of arguments, and argv is a pointer to a pointer of a char
// argv basically acts as a character array
int main(int argc, char** argv) {
	// Only run the main code if the number of arguments is correct
	if (argc == 5) {
		bool tri = false;
		std::string inFile = argv[1];
		std::string outFile = argv[2];
		int length = 0;
		if (isdigit(argv[3][0])) {
			length = atoi(argv[3]);
		} else if (std::string(argv[3]).compare("tri") == 0) {
			tri = true;
		} else {
			std::cout << "Error: Incorrect Third Argument. Needs to be either an integer or 'tri'";
		}

		std::string formatType = argv[4];
		if (length <= 1) {
			std::cout << "Error: Minimum Length Is 2!" << std::endl;
			return -1;
		}
		// Delete all contents from the output file (so you can append to an empty file later)
		std::fstream out;
		out.open(outFile, std::ios::out | std::ios::trunc);
		out.close();

		// From file, generate vector of vectors that acts as the words in the lines
		std::vector<std::vector<std::string>> boxLines = FormulateLines(inFile, length, tri);

		// Flush given vector of vectors
		// Wanted to use switch statement but 
		// C++ doesn't support strings for switch statements :(
		if (formatType == "flush_left" || formatType == "flush_right") {
			// Flush Left And Right Method
			FLARS(boxLines, outFile, length, formatType);
		} else if (formatType == "full_justify") {
			// Full Justify Method
			Full_Justify(boxLines, outFile, length);
		} else {
			std::cout << "Error: Wrong Justification Argument Inputted!" << std::endl;
		}
		// Catch errors for too many or too few arguments
	} else if (argc > 5) {
		std::cout << "Error: Too many arguments!" << std::endl;
		return -1;
	} else {
		std::cout << " Error: Too few arguments!" << std::endl;
		return -1;
	}
	return 1;
}

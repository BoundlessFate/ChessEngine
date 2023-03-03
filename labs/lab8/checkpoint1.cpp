#include <iostream>
void NumPaths(int x, int y, int& count) {
	if (x == 0 && y == 0) {
		count++;
		return;
	}
	if (x == 0) {
		NumPaths(x, y-1, count);
	} else if (y == 0) {
		NumPaths(x-1, y, count);
	} else {
		NumPaths(x-1, y, count);
		NumPaths(x, y-1, count);
	}
	return;
}

int main(int argc, char* argv[]) {
	int count = 0;
	NumPaths(std::stoi(argv[1]), std::stoi(argv[2]), count);
	std::cout << count << " Paths." << std::endl;
	return 1;
}

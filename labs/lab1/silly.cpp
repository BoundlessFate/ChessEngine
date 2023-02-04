#include <iostream>
#include <string.h>

int main(int argc, char** argv) {
	int total = 1;
	for (int i=1; i < argc; ++i) {
		total *= atoi(argv[i]);
	}
	std::cout << total;
	return 0;
}

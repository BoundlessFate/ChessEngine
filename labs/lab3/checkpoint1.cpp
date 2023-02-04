#include <math.h>
#include <iostream>
void compute_squares(unsigned int *a, unsigned int *b, unsigned int n) {
	unsigned int *aPoint;
	unsigned int *bPoint;
	for(aPoint = a, bPoint = b; aPoint < a + n; ++aPoint, ++bPoint) {
	*(bPoint) = pow((*aPoint), 2);
	}
}

int main() {
	unsigned int a[6] = {1, 2, 3, 4, 5, 6};
	unsigned int b[6];
	unsigned int n = 6;
	compute_squares(a, b, n);
	for (unsigned int i=0; i<n; i++) {
		std::cout << b[i] << std::endl;
	}
	return 1;
}

#include "Encoder.h"
#include <algorithm>

int main() {
	Encoder en;

	en.read_file("binaryFile.txt");
	//en.write_file("test_out.txt", "0010111000010001110");
	en.encode("1010");

	int myints[] = { 0,0,1,1 };

	do {
		std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';
	} while (std::next_permutation(myints, myints + 4));
	
	std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';

	return 0;
}
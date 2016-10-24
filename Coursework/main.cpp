#include "Encoder.h"
#include <algorithm>

int main() {
	Encoder en;

	//en.read_file("test1.txt");
	//en.write_file("test_out.txt", "0010111000010001110");
	en.encode("11111");
	
	/*
		000
		001
		010
		011
		100
		101
		110
		111
	*/
	int my_ints[] = { 0,1,2,3 };
	do {
		cout << my_ints[0] << my_ints[1] << my_ints[2] << my_ints[3] << endl;
	} while (std::next_permutation(my_ints, my_ints + 4));

	return 0;
}
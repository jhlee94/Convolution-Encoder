#include "Encoder.h"
#include <algorithm>

int main() {
	Encoder en;

<<<<<<< HEAD
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
=======
	en.read_file("binaryFile.txt");
	//en.write_file("test_out.txt", "0010111000010001110");
	en.encode("1010");

	int myints[] = { 0,0,1,1 };

	do {
		std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';
	} while (std::next_permutation(myints, myints + 4));
	
	std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << ' ' << myints[3] << '\n';
>>>>>>> refs/remotes/origin/master

	return 0;
}
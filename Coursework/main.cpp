#include "Encoder.h"
#include <algorithm>

int main() {
	Encoder en(2, 3);

	//en.read_file("test1.txt");
	//en.write_file("test_out.txt", "0010111000010001110");
	en.encode("1010");
	
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

	//en.generate_seq((string)"0123", (string)"");

	return 0;
}
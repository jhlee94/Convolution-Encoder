#include "Encoder.h"

int main() {
	Encoder en;

	en.read_file("test1.txt");
	//en.write_file("test_out.txt", "0010111000010001110");
	en.encode("0111");
	return 0;
}
#include "Encoder.h"

int main() {
	Encoder en(2, 3);
	//en.compare();
	//en.encode((en.read_file(".\\data\\binaryFile.txt")).c_str());
	en.encode("1010");

	return 0;
}
#include "Encoder.h"
#define TO_INT(x) (int)x - 48


Encoder::Encoder()
{
	registers = new bool[MAX_REGISTER_NUM];
	for (int i = 0; i < MAX_REGISTER_NUM; i++) {
		registers[i] = false;
	}
}


Encoder::~Encoder()
{
	delete[] registers;
}

void Encoder::read_file(const char* filename) {
	ifstream infile(filename);
	if (infile.is_open()) {
		for (string line; getline(infile, line);) {
			cout << line << endl;
		}
		infile.close();
	}
}

void Encoder::write_file(const char* filename, const char* message) {
	ofstream outfile;
	outfile.open(filename);

	outfile << message << endl;
	outfile.close();
}

void Encoder::encode(const char* message) {
	size_t size = strlen(message);
	
	string s;
	bool* hour, *minute, *second;
	hour = &registers[0];
	minute = &registers[1];
	second = &registers[2];

	for (int i = 0; i < size; i++) {
		// XOR encoding step here
		s = s + to_string(XOR().result(TO_INT(message[i]), *hour)) + to_string(XOR().result(*minute, *second)) + ' ';

		////XOR1
		//	int xor1 = registers[0] != registers[1];

		////XOR2
		//	int xor2 = TO_INT(message[i]) != registers[0];

		//	s = s + to_string(xor2) + to_string(xor1) + ' ';

		bool input_bit = TO_INT(message[i]);
		shift(registers, input_bit);
	}
	cout << s << endl;
}

void Encoder::shift(bool*& registers, bool &input_bit) {
	for (int i = MAX_REGISTER_NUM - 1; i >= 0; i--) {
		if (i == 0) {
			registers[0] = input_bit;
		}
		else {
			registers[i] = registers[i - 1];
		}
	}
}
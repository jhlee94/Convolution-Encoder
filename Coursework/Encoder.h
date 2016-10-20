#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <bitset> 

using namespace std;

class Encoder
{
public:
	Encoder();
	~Encoder();
	
	void read_file(const char* filename);
	void write_file(const char* filename, const char* message);
	void encode(const char* message);
	void shift(bool*& registers, bool &input_bit);

	const int MAX_REGISTER_NUM = 3;
protected:

private:
	bool* registers;

};


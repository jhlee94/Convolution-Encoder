#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>
#include "XOR.h"

using namespace std;

class Encoder
{
public:
	Encoder();
	Encoder(int gate, int reg);
	~Encoder();
	
	void encode(const char* message);
	string read_file(const char* filename);

	const int DEFAULT_REGISTER_NUM = 3;
	void compare();

protected:
	void generate_seq(string &str, string sequence);
	void write_file(const char* filename, const char* message);

private:
	void shift(bool*& registers, bool input_bit);
	void reset();

	bool* registers;
	int gates_num;
	int reg_num;
	vector<XOR> gates;
	vector<string> sequences;
};


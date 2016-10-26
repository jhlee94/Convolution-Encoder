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
	
	void read_file(const char* filename);
	void write_file(const char* filename, const char* message);
	void encode(const char* message);
	void shift(bool*& registers, bool &input_bit);

	void generate_seq(string &str, string sequence);

	const int DEFAULT_REGISTER_NUM = 3;
protected:

private:
	void reset();

	bool* registers;
	int gates_num;
	int reg_num;
	vector<XOR> gates;
	vector<string> sequences;
};


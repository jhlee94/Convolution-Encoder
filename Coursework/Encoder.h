#pragma once
#include <iostream>
#include <string>
#include <fstream>
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

	void compare();

	vector<string> sequences;
protected:
	void generate_seq(string &c, int n, string sequence);
	void write_file(const char* filename, const char* message);

private:
	void shift(bool*& registers, bool input_bit);
	void reset();

	bool* registers;
	int gates_num;
	int reg_num;
	int total_leg_count;
	vector<XOR> gates;

	const int DEFAULT_REGISTER_NUM = 3;
	const int DEFAULT_GATE_NUM = 2;
};


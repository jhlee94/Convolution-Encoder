// Author: Jong Hoon Lee, Student Number: 130329288
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "General.h"
#include "XOR.h"

using namespace std;

class Encoder
{
public:
	Encoder();
	Encoder(int gate, int reg);
	Encoder(string leg_format);
	~Encoder();
	
	void encode(const char* message);
	string read_file(const char* filename);

	void compare(int &choice);

	vector<string> sequences;
protected:
	void generate_seq(string &c, int n, string sequence);
	void write_file(const char* filename, const char* message);

private:
	void shift(bool*& registers, bool input_bit);
	bool process_input(string &s);
	void reset();

	bool* registers;
	int gates_num;
	int reg_num;
	int total_leg_count;
	vector<XOR> gates;

	const int DEFAULT_REGISTER_NUM = 3;
	const int DEFAULT_GATE_NUM = 2;
};


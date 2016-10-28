// Author: Jong Hoon Lee, Student Number: 130329288
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include "General.h"
#include "XOR.h"

using namespace std;

struct Node {
public:
	int key;
	int metric;
	Node* zero;
	Node* one;
};

class Decoder
{
public:
	Decoder();
	Decoder(int reg_num);
	~Decoder();

	void decode(string msg, string filename);
	void generate_states(string &sequence);
	void print_decoded_message();
	void load(vector<string> &sequences);
	

	string read_file(const char* filename);
	void write_file(const char* filename, const char* message);
	void inject_error(vector<string> &sequences);

	void reset();

	vector<string*> state_map;
	vector<string> messages;
	vector<string> err_msgs;
	string sequence;
	string answer;

private:
	void process(Node **leaf, int key, int metric, string &state, string msg);

	void generate_seq(unsigned int n);
	void print_decoded_message(Node* p);

	int calc_hamming_distance(string &a, string &b);
	void convertToBinary(int n, string &sequence);

	string* find(string state);

	void terminate_tree(Node *leaf);

	Node *root;
	int reg_num;
	int count;
	const int DEFAULT_REG_NUM = 3;
};


#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
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

	void decode(string msg);
	void generate_states(string &sequence);
	void print_decoded_message();
	void reset();

	vector<string*> state_map;
	string answer;

private:
	void process(Node **leaf, int key, int metric, string &state, string msg);
	void inject_error();

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


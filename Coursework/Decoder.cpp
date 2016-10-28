#include "Decoder.h"

Decoder::Decoder()
{
	reg_num = DEFAULT_REG_NUM;
	root = new Node();
	root->key = -1;
	root->metric = -1;
}

Decoder::Decoder(int reg_num)
{
	this->reg_num = reg_num;
}

Decoder::~Decoder()
{
	for (int i = 0; i < state_map.size(); i++) {
		if (state_map.at(i) != NULL) {
			delete[] state_map.at(i);
			state_map.at(i) = NULL;
		}
	}
	state_map.clear();
	terminate_tree(root);
}


void Decoder::decode(string msg) {
	process(&root, -1, -1, state_map.at(0)[0] , msg);
}


void Decoder::process(Node **leaf, int key, int metric, string &state, string msg) {
	string* state_ptr;

	int metric_zero_temp = -1, metric_one_temp = -1;
	string new_zero_state, zero_output, new_one_state, one_output;

	// calculate states and add
	string enc_msg_bit = msg.substr(0, 2);

	if (!(*leaf)) {
		(*leaf) = new Node();
		(*leaf)->key = key;
		(*leaf)->metric = metric;
		(*leaf)->zero = NULL;
		(*leaf)->one = NULL;
		count++;
	}
	if (msg.length() >= 2) {

		// zero
		state_ptr = find(state);
		new_zero_state = state_ptr[1];
		zero_output = state_ptr[2];
		// calculate metric
		metric_zero_temp = calc_hamming_distance(zero_output, enc_msg_bit);

		// one
		state_ptr = find(state);
		new_one_state = state_ptr[3];
		one_output = state_ptr[4];

		metric_one_temp = calc_hamming_distance(one_output, enc_msg_bit);
		if (metric_zero_temp <= metric_one_temp) {
			process(&((*leaf)->zero), 0, metric_zero_temp, new_zero_state, msg.substr(2, msg.length() - 1));
		}
		else {
			process(&((*leaf)->one), 1, metric_one_temp, new_one_state, msg.substr(2, msg.length() - 1));
		}
	}
}

void Decoder::reset() {
	for (int i = 0; i < state_map.size(); i++) {
		if (state_map.at(i) != NULL) {
			delete[] state_map.at(i);
			state_map.at(i) = NULL;
		}
	}
	state_map.clear();
	terminate_tree(root);

	reg_num = DEFAULT_REG_NUM;
	root = new Node();
	root->key = -1;
	root->metric = -1;
	answer = "";
}

string* Decoder::find(string state) {
	for (int i = 0; i < state_map.size(); i++) {
		if (!state_map.at(i)[0].compare(state)) {
			return state_map.at(i);
		}
	}
	return NULL;
}

void Decoder::inject_error() {
	
}

void Decoder::generate_states(string &sequence) {
	generate_seq(reg_num);
	string inputs;

	for (int i = 0; i < state_map.size(); i++) {
		for (int j = 1; j < 5; j++) { 
			switch (j) {
			case 1:
				// Case 0: shift state
				state_map.at(i)[j] = "0" + state_map.at(i)[0].substr(0, reg_num - 1);
				break;
			case 2:
				// Case 0: calculate output
				inputs = "0" + state_map.at(i)[0];
				state_map.at(i)[j] = to_string(XOR().process(TO_INT(inputs.at(TO_INT(sequence.at(0)))), TO_INT(inputs.at(TO_INT(sequence.at(1))))))
										+ to_string(XOR().process(TO_INT(inputs.at(TO_INT(sequence.at(1)))), TO_INT(inputs.at(TO_INT(sequence.at(2))))));
				break;
			case 3:
				// Case 1: shift state
				state_map.at(i)[j] = "1" + state_map.at(i)[0].substr(0, reg_num - 1);
				break;
			case 4:
				// Case 1: calculate output
				inputs = "1" + state_map.at(i)[0];
				state_map.at(i)[j] = to_string(XOR().process(TO_INT(inputs.at(TO_INT(sequence.at(0)))), TO_INT(inputs.at(TO_INT(sequence.at(1))))))
					+ to_string(XOR().process(TO_INT(inputs.at(TO_INT(sequence.at(1)))), TO_INT(inputs.at(TO_INT(sequence.at(2))))));
				break;
			default:
				break;
			}
		}
	}
}

void Decoder::generate_seq(unsigned int n) {
	string s;
	for (int i = 0; i < pow(2, n); i++) {
		string *state = new string[5];
		convertToBinary(i, state[0]);
		state[0] = string(n - state[0].length(), '0').append(state[0]);
		state_map.push_back(state);
	}
}


void Decoder::convertToBinary(int n, string &sequence) {
	if (n / 2 != 0) {
		convertToBinary(n / 2, sequence);
	}
	sequence += to_string(n % 2);
}


int Decoder::calc_hamming_distance(string &a, string &b) {
	int count = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a.at(i) != b.at(i)) {
			count++;
		}
	}

	return count;
}

void Decoder::terminate_tree(Node *leaf) {
	if (leaf != NULL)
	{
		terminate_tree(leaf->zero);
		terminate_tree(leaf->one);
		delete leaf;
	}
}

void Decoder::print_decoded_message() {
	print_decoded_message(root);
}

void Decoder::print_decoded_message(Node* p)
{
	if (p != NULL) {
		if (p != root) {
			std::cout << p->key << " ";
			answer += to_string(p->key);
		}
		
		if (p->zero) print_decoded_message(p->zero);
		if (p->one) print_decoded_message(p->one);
	}
	else
		std::cout << "The tree is empty" << std::endl;
}


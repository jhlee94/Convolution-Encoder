// Author: Jong Hoon Lee, Student Number: 130329288
#include "Encoder.h"


Encoder::Encoder()
{
	registers = new bool[DEFAULT_REGISTER_NUM];
	for (int i = 0; i < DEFAULT_REGISTER_NUM; i++) {
		registers[i] = false;
	}
	reg_num = DEFAULT_REGISTER_NUM;

	total_leg_count = 0;
	for (int i = 0; i < DEFAULT_GATE_NUM; i++) {
		XOR gate;
		gates.push_back(gate);
		total_leg_count += gate.leg_num;
	}

	string permutations;
	for (int i = 0; i < reg_num + 1; i++) {
		permutations = permutations + to_string(i);
	}
	generate_seq(permutations, total_leg_count, "");
}

Encoder::Encoder(int gate, int reg) :
	gates_num(gate), reg_num(reg) 
{
	registers = new bool[reg_num];
	for (int i = 0; i < reg_num; i++) {
		registers[i] = false;
	}
	total_leg_count = 0;
	for (int i = 0; i < gates_num; i++) {
		XOR gate;
		gates.push_back(gate);
		total_leg_count += gate.leg_num;
	}

	string permutations;
	for (int i = 0; i < reg_num + 1; i++) { // change this so that it depends on total number of legs
		permutations = permutations + to_string(i);
	}
	generate_seq(permutations, total_leg_count, "");
};

Encoder::Encoder(string leg_format) {
	if (process_input(leg_format)) {
		string permutations;
		for (int i = 0; i < reg_num + 1; i++) { // change this so that it depends on total number of legs
			permutations = permutations + to_string(i);
		}
		generate_seq(permutations, total_leg_count, "");
	}
	else {
		Encoder();
	}
}


Encoder::~Encoder()
{
	sequences.clear();
	delete[] registers;
}

string Encoder::read_file(const char* filename) {
	string message;
	ifstream infile(filename);
	if (infile.is_open()) {
		for (string line; getline(infile, line);) {
			message += line;
		}
		infile.close();
	}
	return message;
}

void Encoder::write_file(const char* filename, const char* message) {
	ofstream outfile;
	outfile.open(filename);

	outfile << message << endl;
	outfile.close();
}

/*	Encoding function which utilises pre-generated permutations stored in a vector.
*	Each index represents the index of registers or input bit. 
*	The total number of permutation varies depending on the total number of legs
*	and number of registers.
*/

void Encoder::encode(const char* message) {
	size_t size = strlen(message);
	
	string enc_msg, permutations, crnt_seq;

	vector<bool*> bits(reg_num+1);

	for (int i = 1; i < reg_num + 1; i++) {
		bits.at(i) = &registers[i-1];
	}
	
	int *xor_leg_ptr = new int(0);

	for (int s = 0; s < sequences.size(); s++) {
		reset();
		enc_msg = "";
		crnt_seq = sequences.at(s);

		for (int i = 0; i < size; i++) {
			*xor_leg_ptr = 0; // xor leg pointer to the sequence i.e. s = "0123", 0 is first leg, 1 is second leg and so on

			bool msg = TO_INT(message[i]);
			bits.at(0) = &msg;

			// XOR encoding step here
			for (int g = 0; g < gates.size(); g++) {
				gates.at(g).reset();
				for (int l = 0; l < gates.at(g).leg_num; l++) {
					gates.at(g).add(*bits.at(TO_INT(crnt_seq.at(*xor_leg_ptr))));
					(*xor_leg_ptr)++;
				}
				enc_msg += to_string(gates.at(g).process());
			}

			shift(registers, TO_INT(message[i]));
		}

		string filename = ENCODE_FILENAME(s);
		write_file(filename.c_str(), enc_msg.c_str());
	}

	delete xor_leg_ptr;
	xor_leg_ptr = NULL;
}

void Encoder::shift(bool*& registers, bool input_bit) {
	for (int i = reg_num - 1; i >= 0; i--) {
		if (i == 0) {
			registers[0] = input_bit;
		}
		else {
			registers[i] = registers[i - 1];
		}
	}
}

void Encoder::reset() {
	for (int i = 0; i < reg_num; i++) {
		registers[i] = false;
	}
}

void Encoder::generate_seq(string &c, int n, string sequence) {
	
	if (sequence.length() >= n) {
		//System.out.println(start)
		//cout << sequence << endl;
		sequences.push_back(sequence);

	}
	else {
		for (char x : c) {
			generate_seq(c, n, sequence + x);
		}
	}
}


void Encoder::compare(int &choice) {
	vector<string> messages, marcus;
	for (int i = 0; i < sequences.size(); i++) {
		string filename = ENCODE_FILENAME(i);
		messages.push_back(read_file(filename.c_str()));
	}
	int *counter;
	if (choice) { //compare with marcus's data
		for (int i = 0; i < sequences.size(); i++) {
			string filename2 = ".\\data\\MethodClass-Marcus\\MethodClass-" + to_string(i) + ".txt";
			marcus.push_back(read_file(filename2.c_str()));
		}

		int count = 0;
		for (int i = 0; i < sequences.size(); i++) {
			cout << i << ": " << " (" << sequences.at(i) << ")" << endl;
			if (!messages.at(i).compare(marcus.at(i))) {
				cout << i << " and marcus " << i << " are same." << endl;
				count++;
			}
		}
		cout << count << endl;
	}
	else { // Compare using own encoded files (finding permutation which gives same output)
		counter = new int[sequences.size()];
		counter[messages.size() - 1] = 0;
		for (int i = 0; i < messages.size()-1; i++) {
			counter[i] = 0;
			for (int j = i + 1; j < messages.size(); j++) {
				if (!messages.at(i).compare(messages.at(j))) {
					counter[i]++;
				}
			}
		}

		cout << "***************************************************" << endl;
		cout << left << "Sequence Number\tSequence\tNo.Duplicates" << endl;
		for (int i = 0; i < sequences.size(); i++) {
			cout << left << i << "\t\t" << sequences.at(i) << "\t\t" << counter[i] << endl;
		}
		delete[] counter;
	}
}

// For User Interface interact check
bool Encoder::process_input(string &s) {
	std::vector<int> vect;

	std::stringstream ss(s);

	int i;

	while (ss >> i)
	{
		vect.push_back(i);

		if (ss.peek() == ',' || ss.peek() == ' ')
			ss.ignore();
	}

	if ((vect.size() - 2) != vect.at(1)) {
		cout << "Initialise failed please check your syntax!!"<<endl;
		return false;
	}
	else {
		reg_num = vect.at(0);
		gates_num = vect.at(1);

		registers = new bool[reg_num];
		for (int i = 0; i < reg_num; i++) {
			registers[i] = false;
		}

		total_leg_count = 0;

		int j = 2;

		for (int i = 0; i < gates_num; i++) {
			XOR gate;
			gate.leg_num = vect.at(j);
			gates.push_back(gate);
			total_leg_count += gate.leg_num;
			j++;
		}
	}

	return 1;
}
#include "Encoder.h"
#define TO_INT(x) (int)x - 48
#define TO_CHAR(x) to_string(x +48);


Encoder::Encoder()
{
	registers = new bool[DEFAULT_REGISTER_NUM];
	for (int i = 0; i < DEFAULT_REGISTER_NUM; i++) {
		registers[i] = false;
	}
	reg_num = DEFAULT_REGISTER_NUM;

	string permutations;
	for (int i = 0; i < reg_num + 1; i++) {
		permutations = permutations + to_string(i);
	}
	generate_seq(permutations, "");
}

Encoder::Encoder(int gate, int reg) :
	gates_num(gate), reg_num(reg) 
{
	registers = new bool[reg_num];
	for (int i = 0; i < reg_num; i++) {
		registers[i] = false;
	}

	for (int i = 0; i < gates_num; i++) {
		gates.push_back(XOR());
	}
	string permutations;
	for (int i = 0; i < reg_num + 1; i++) { // change this so that it depends on total number of legs
		permutations = permutations + to_string(i);
	}
	generate_seq(permutations, "");
};


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
			*xor_leg_ptr = 0; // if the total number of leg is larger than the total number of bits 
							  // then this needs constraint in order to avoid wrongly pointed pointer
			bool msg = TO_INT(message[i]);
			bits.at(0) = &msg;

			// XOR encoding step here
			
			for (int g = 0; g < gates.size(); g++) {
				gates.at(g).empty();
				for (int l = 0; l < gates.at(g).leg_num; l++) {
					gates.at(g).add(*bits.at(TO_INT(crnt_seq.at(*xor_leg_ptr))));
					(*xor_leg_ptr)++;
				}
				enc_msg += to_string(gates.at(g).process());
			}

			shift(registers, TO_INT(message[i]));
		}

		string filename = ".\\data\\" + to_string(s) + " (" + crnt_seq + ").txt";
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

void Encoder::generate_seq(string &str, string sequence) {

	if (sequence.length() == str.length()) {
		sequences.push_back(sequence);
		return ;
	}

	for (int i = 0; i < str.length(); i++) {
		generate_seq(str, sequence + str.at(i));
	}
}


void Encoder::compare() {
	vector<string> messages, marcus;

	for (int i = 0; i < sequences.size(); i++) {
		string filename = ".\\data\\" + to_string(i) + " (" + sequences.at(i) + ").txt";
		string filename2 = ".\\data\\MethodClass-Marcus\\MethodClass-" + to_string(i) + ".txt";
		messages.push_back(read_file(filename.c_str()));
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
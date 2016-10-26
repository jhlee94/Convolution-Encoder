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
};


Encoder::~Encoder()
{
	delete[] registers;
}

void Encoder::read_file(const char* filename) {
	ifstream infile(filename);
	if (infile.is_open()) {
		for (string line; getline(infile, line);) {
			cout << line << endl;
		}
		infile.close();
	}
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

	for (int i = 0; i < reg_num + 1; i++) {
		permutations = permutations + to_string(i);
		
		if (i > 0) {
			bits.at(i) = &registers[i-1];
		}
	}

	generate_seq(permutations, "");
		
	for (int s = 0; s < sequences.size(); s++) {
		reset();
		enc_msg = "";
		crnt_seq = sequences.at(s);

		for (int i = 0; i < size; i++) {
			bool msg = TO_INT(message[i]);
			bits.at(0) = &msg;
			// XOR encoding step here

			enc_msg = enc_msg 
				+ to_string(XOR().result(*bits.at(TO_INT(crnt_seq.at(0))), *bits.at(TO_INT(crnt_seq.at(1))))) 
				+ to_string(XOR().result(*bits.at(TO_INT(crnt_seq.at(2))), *bits.at(TO_INT(crnt_seq.at(3))))) + ' ';

			bool input_bit = TO_INT(message[i]);
			shift(registers, input_bit);
		}

		cout  << s << " (" << crnt_seq << ") " << ':' << ' ' << enc_msg << endl;
	}
}

void Encoder::shift(bool*& registers, bool &input_bit) {
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
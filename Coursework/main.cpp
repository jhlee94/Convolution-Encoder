// Author: Jong Hoon Lee, Student Number: 130329288

#include "Encoder.h"
#include "Decoder.h"
#include <iomanip>

void Execute_Encoder();
void Execute_Decoder();

int count_different_bits(string &str, string &str2);

Encoder *enc;
Decoder *decoder;

int main() {
	Execute_Encoder();
	system("cls");
	Execute_Decoder();

	return 0;
}

void Execute_Encoder() {
	int x = 0;

	cout << "WELCOME TO CONVOLUTIONAL ENCODER" << endl;
	while (x != 6) {
		x = 0;
		cout << "=========================================" << endl;
		cout << "Please choose an operation from the below" << endl;
		cout << "-----------------------------------------" << endl;
		cout << "1. Initialise encoder with sepecific" << endl;
		cout << "   number of registers, XOR gates, and" << endl;
		cout << "   its number of legs." << endl;
		cout << "2. Initialise default encoder." << endl;
		cout << "3. Encode personal message." << endl;
		cout << "4. Encode given binary file." << endl;
		cout << "5. Compare encoded files." << endl;
		cout << "6. Terminate the program." << endl;
		cout << "========================================" << endl;
		cin >> x;

		string spec_format = "";
		string p_msg = "";
		switch (x)	
		{
		case 1:
			system("cls");
			cout << "Please enter number of registers, number of" << endl;
			cout << "gates and leg numbers for each xor gate in" << endl;
			cout << "the given format." << endl;
			cout << "i.e. 3 registers, 2 xor gates with 2 and 3 leg numbers" << endl;
			cout << "respectively: 3, 2, 2, 3" << endl;
			cin.ignore();
			getline(cin, spec_format);
			delete enc;
			enc = new Encoder(spec_format);
			spec_format = "";
			break;
		case 2:
			system("cls");
			enc = new Encoder();
			break;
		case 3:
			system("cls");
			cout << "Please enter message with 1s and 0s." << endl;
			cin.ignore();
			getline(cin, p_msg);
			enc->encode(p_msg.c_str());
			cout << "Saved!!" << endl;
			p_msg = "";
			break;
		case 4:
			system("cls");
			cout << "!CAUTION! This will override the existing" << endl;
			cout << "files if there is any. 0 to stop, 1 to continue." << endl;
			cin >> x;
			if (x) {
				enc->encode(enc->read_file(CW2_BINARY_FILE).c_str());
				cout << "Saved!!" << endl;
			}
			break;
		case 5:
			system("cls");
			if (enc != NULL) {
				cout << "0 = compare encoded files, 1 = compare with Marcus's files." << endl;
				cin.ignore();
				cin >> x;
				enc->compare(x);
			}
			else {
				cout << "Please check if you have sufficient files" << endl;
				cout << "and initialised the encoder." << endl;
			}
			break;
		case 6:
			delete enc;
			break;
		default:
			break;
		}
	}
}


void Execute_Decoder() {
	// Coursework 2
	decoder = new Decoder();
	enc = new Encoder();
	decoder->load(enc->sequences);

	int count = 0;
	int err_count = 0;
	int compare = 0;

	string original_msg = enc->read_file(CW2_BINARY_FILE);
	string comparison_msg = "";
	string filename;

	for (int s = 0; s < enc->sequences.size(); s++) {
		//Non-Error
		decoder->reset();
		decoder->generate_states(enc->sequences.at(s));

		filename = DECODE_FILENAME(s);
		decoder->decode(decoder->messages.at(s), filename.c_str());
		if (!decoder->answer.compare("10101100")) {
			cout << "Non-error " << s << " is correct." << endl;
			count++;
		}
		else {
			compare = count_different_bits(decoder->answer, string("10101100"));
			cout << "Non-error " << s << " has " << compare << " bits off target." << endl;
		}
	}

	for (int s = 0; s < enc->sequences.size(); s++) {
		//Error
		decoder->reset();
		decoder->generate_states(enc->sequences.at(s));
		filename = ERR_DECODE_FILENAME(s, enc->sequences.at(s));
		decoder->decode(decoder->err_msgs.at(s), filename.c_str());

		if (!decoder->answer.compare("10101100")) {
			cout << "Error " << s << " is correct." << endl;
			err_count++;
		}
		else {
			compare = count_different_bits(decoder->answer, string("10101100"));
			cout << "Error " << s << " has " << compare << " bits off target." << endl;
		}
	}
	cout << "Total number of correctly decoded files (No-Error): " <<  count << endl;
	cout << "Total number of correctly decoded files (With Error): " << err_count << endl;

	delete decoder;
	delete enc;
}

int count_different_bits(string &str, string &str2) {
	int counter = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != str2[i]) {
			counter++;
		}
	}
	return counter;
}
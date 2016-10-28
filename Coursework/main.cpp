#include "Encoder.h"
#include "Decoder.h"
#include "BST.h"

int main() {

	Encoder en(2, 3);
	//en.encode((en.read_file(".\\data\\binaryFile.txt")).c_str());
	//en.compare();
	en.encode("1010");

	//Decoder de;

	//vector<string> messages;
	//int count = 0;

	//for (int i = 0; i < en.sequences.size(); i++) {
	//	string filename = ".\\data\\" + to_string(i) + " (" + en.sequences.at(i) + ").txt";
	//	//string filename2 = ".\\data\\MethodClass-Marcus\\MethodClass-" + to_string(i) + ".txt";
	//	messages.push_back(en.read_file(filename.c_str()));
	//}

	//for (int s = 0; s < en.sequences.size(); s++) {
	//	de.reset();
	//	de.generate_states(en.sequences.at(s));

	//	/*for (int i = 0; i < de.state_map.size(); i++) {
	//		for (int j = 0; j < 5; j++) {
	//			cout << de.state_map.at(i)[j] << ' ';
	//		}
	//		cout << endl;
	//	}*/
	//	de.decode(messages.at(s));
	//	de.print_decoded_message();
	//	if (de.answer.compare("1000101010"))
	//		count++;
	//	cout << endl;
	//}
	////de.decode(en.read_file(".\\data\\binaryFile.txt"));
	//cout << count << endl;

	return 0;
}
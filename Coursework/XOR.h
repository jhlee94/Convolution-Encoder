#pragma once
#include <vector>
#include <string>
class XOR
{
public:
	XOR() {
		leg_num = 0;
	}
	XOR(int &leg_num, std::vector<int> inputs) : leg_num(leg_num), inputs(inputs){};
	~XOR() {};

	bool result(int first, int second) { return first != second; }
	
	bool process();

	std::vector<int> getInput() {
		return inputs;
	}
private:
	int leg_num;
	std::vector<int> inputs;
};
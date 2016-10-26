#pragma once
#include <vector>
#include <string>
class XOR
{
public:
	XOR() {
		leg_num = 2;
	}
	XOR(int &leg_num) : leg_num(leg_num) {};
	~XOR() {};

	void add(int input) {
		result += input;
	}
	
	bool process() {
		return result % 2;
	}

	void empty() {
		result = 0;
	}

	int leg_num;
private:
	int result;
};
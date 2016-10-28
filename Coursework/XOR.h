#pragma once
#include <vector>
#include <string>
#define TO_INT(x) (int)x - 48

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

	bool process(int a, int b) {
		return (a + b) % 2;
	}

	void reset() {
		result = 0;
	}

	int leg_num;
private:
	int result;
};
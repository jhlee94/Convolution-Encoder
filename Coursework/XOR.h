// Author: Jong Hoon Lee, Student Number: 130329288
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

	bool process(int a, int b) {
		return (a + b) % 2; // simple modular-2 addition (XOR)
	}

	void reset() {
		result = 0;
	}

	int leg_num;
private:
	int result;
};
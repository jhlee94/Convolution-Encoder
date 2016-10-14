#pragma once
#include <stdio.h>

class Encoder
{
public:
	Encoder();
	~Encoder();

	const int MAX_REGISTER_NUM = 3;
protected:

private:
	bool* registers;

};


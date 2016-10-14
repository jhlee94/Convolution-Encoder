#include "Encoder.h"



Encoder::Encoder()
{
	registers = new bool[MAX_REGISTER_NUM];
}


Encoder::~Encoder()
{
	delete[] registers;
}

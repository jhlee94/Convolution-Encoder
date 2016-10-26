#pragma once
class Decoder
{
public:
	Decoder();
	~Decoder();

	void decode();
	void inject_error();

	bool BURST_MODE;
};


// Author: Jong Hoon Lee, Student Number: 130329288
#pragma once

#define TO_INT(x) (int)x - 48
#define TO_CHAR(x) char(x + 48)

#define DECODE_FILENAME(s) ".\\data\\decode\\" + to_string(s) + " dec_(" + enc->sequences.at(s) + ").txt"
#define ERR_DECODE_FILENAME(s,m) ".\\data\\error\\decode\\" + to_string(s) + " dec_(" + m + ")_err.txt"

#define ENCODE_FILENAME(s) ".\\data\\encode\\" + to_string(s) + " (" + sequences.at(s) + ").txt"
#define ERR_ENCODE_FILENAME(s) ".\\data\\error\\encode\\" + to_string(s) + " (" + sequences.at(s) + ")_err.txt"


static const char* CW2_BINARY_FILE = ".\\data\\binaryFile.txt";
#include <fstream>
#include "pipe.h"
#include <string>
#include <iomanip>
#include "macros.h"
using namespace std;

#ifndef FETCH_H
#define FETCH_H
#define MI_filename "ISA.txt"

SC_MODULE (fetch)
{
	ifstream MI;
	sc_in <bool> clk;
	sc_out < sc_uint<INSTRUCTION_SIZE> > instruction_in;

	void Fetch()
	{
		string line;
		getline(MI,line);
		sc_uint <INSTRUCTION_SIZE> temp;

		for (int i = 0; i < INSTRUCTION_SIZE; ++i) 
			temp[i] = line[INSTRUCTION_SIZE-(i+1)]-'0';

		instruction_in.write(temp);
	}

	SC_CTOR (fetch)
	{
		MI.open(MI_filename);
		SC_METHOD(Fetch);
		sensitive << clk.neg();
	}

	~fetch()
	{
		MI.close();
	}
};

#endif
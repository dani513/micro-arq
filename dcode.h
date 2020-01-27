#ifndef DCODE_H
#define DCODE_H

#include <string>
#include <iomanip>
#include "macros.h"
using namespace std;

SC_MODULE (Dcode)
{
  sc_in <bool> clk;
  sc_in < sc_uint < INSTRUCTION_SIZE > > instruction_to_decode;
  sc_out < sc_uint < INSTRUCTION > > instruction;
  sc_out < sc_uint < INSTRUCTION > > op1, op2, res;
  sc_uint < INSTRUCTION > temp;

  void dcode()
  {
    instruction.write(instruction_to_decode.read().range(3, 0));
    op1.write(instruction_to_decode.read().range(7, 4));
    op2.write(instruction_to_decode.read().range(11, 8));
    res.write(instruction_to_decode.read().range(15, 12));
  }
  
  SC_CTOR (Dcode)
  {
    SC_METHOD(dcode);
    sensitive << clk.pos();
  }
  
  ~Dcode(){  }
};

#endif

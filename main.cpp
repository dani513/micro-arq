#include <systemc.h>
#include <string>
#include <iomanip>
#include "pipe.h"
#include "dcode.h"
#include "macros.h"
#include "fetch.h"
#include "testbench.h"

int sc_main(int argv, char* argc[])
{
  sc_time PERIOD(10, SC_NS);
  sc_time DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);
  
  Fetch ft("fetch");
  Dcode dcode("dcode");
  Testbench tb("tb");
  
  
  sc_signal < sc_uint<INSTRUCTION> > decoded_instruction_sg, op1_sg, op2_sg, res_sg;
  sc_signal < sc_uint<INSTRUCTION_SIZE> >instruction_in_sg;
  
  ft.instruction_in(instruction_in_sg);
  ft.clk(clock);
  
  dcode.clk(clock);
  dcode.instruction_to_decode(instruction_in_sg);
  dcode.instruction(decoded_instruction_sg);
  dcode.op1(op1_sg);
  dcode.op2(op2_sg);
  dcode.res(res_sg);

  tb.clk(clock);
  tb.instruction(decoded_instruction_sg);
  tb.op1(op1_sg);
  tb.op2(op2_sg);
  tb.res(res_sg);

  
  sc_start();
  return 0;
}

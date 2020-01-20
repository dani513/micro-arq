#include <systemc.h>
#include <string>
#include <iomanip>
#include "macros.h"
#include "fetch.h"
#include "testbench.h"

int sc_main(int argv, char* argc[])
{
  sc_time PERIOD(10, SC_NS);
  sc_time DELAY(10, SC_NS);
  sc_clock clock("clock", PERIOD, 0.5, DELAY, true);
  
  fetch ft("fetch");
  testbench tb("tb");
  Pipe p1("pipe1");
  Pipe p2("pipe2");
  Pipe p3("pipe3");
  
  sc_signal < sc_uint<INSTRUCTION_SIZE> > instruction_in_sg, pipe12_sg , pipe23_sg, pipe34_sg;
  
  ft.instruction_in(instruction_in_sg);
  ft.clk(clock);
  
  tb.tb_in(instruction_in_sg);
  tb.clk(clock);
  tb.pipe1(pipe12_sg);
  tb.pipe2(pipe23_sg);
  tb.pipe3(pipe34_sg);
  
  p1.pi_in(instruction_in_sg);
  p1.pi_out(pipe12_sg);
  p1.clk_in(clock);
  
  p2.pi_in(pipe12_sg);
  p2.pi_out(pipe23_sg);
  p2.clk_in(clock);
  
  p3.pi_in(pipe23_sg);
  p3.pi_out(pipe34_sg);
  p3.clk_in(clock);
  
  sc_start();
  return 0;
}

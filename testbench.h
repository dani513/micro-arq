#ifndef TESTBENCH
#define TESTBENCH

#include <iomanip>
#include "macros.h"

SC_MODULE(testbench)
{
  sc_in < sc_uint < INSTRUCTION_SIZE> > tb_in;
  sc_in <bool> clk;
  sc_in < sc_uint < INSTRUCTION_SIZE> > pipe1, pipe2, pipe3;

  void print()
  {
    cout<< setw(6);
    for (int i = 0; i < INSTRUCTION_SIZE; ++i) //Imprime las instrucciones en binario
      cout<< tb_in.read().range(INSTRUCTION_SIZE-(i+1),INSTRUCTION_SIZE-(i+1));

    cout<<setw(4);
    cout << "  | " << setw(5) << tb_in.read() << " |  "  << clk.read() <<"  | "; //Imprime las instrucciones en decimal y el clock

    for (int i = 0; i < INSTRUCTION_SIZE; ++i)// Imprime el primer pipe
      cout << pipe1.read().range(INSTRUCTION_SIZE-(i+1),INSTRUCTION_SIZE-(i+1));

    cout << " | ";

    for (int i = 0; i < INSTRUCTION_SIZE; ++i)// Imprime el segundo pipe
      cout << pipe2.read().range(INSTRUCTION_SIZE-(i+1),INSTRUCTION_SIZE-(i+1));
    
    cout << " | ";

    for (int i = 0; i < INSTRUCTION_SIZE; ++i)// Imprime el tercer pipe
      cout << pipe3.read().range(INSTRUCTION_SIZE-(i+1),INSTRUCTION_SIZE-(i+1));

    cout << " | "; cout <<"\n";
  }

  void test()
  {
    cout << "\nInstruccion|Decimal|Clock|Pipe 1|Pipe 2|Pipe 3|\n"
         << "------------------------------------------------\n";

    for (int i = 0; i < INSTRUCTIONS; ++i)
    {
      wait();
      print();
    }
    
    sc_stop();
  }

  SC_CTOR(testbench)
  {
    SC_THREAD(test);
    sensitive << clk.neg();
  }
};

#endif
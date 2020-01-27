#ifndef TESTBENCH
#define TESTBENCH

#include <iomanip>
#include "macros.h"

SC_MODULE(Testbench)
{
  sc_in <bool> clk;
  sc_in < sc_uint < INSTRUCTION> > instruction, op1, op2, res;
  // sc_in < sc_uint < INSTRUCTION_SIZE> > pipe1 /*, pipe2, pipe3*/;

  void print(){
    cout << setw(4);
    for (int i = 0; i < INSTRUCTION; ++i) //Imprime la instrucciones en binario
      cout << instruction.read().range(INSTRUCTION-(i+1),INSTRUCTION-(i+1));
    cout << setw(7) << "|  ";

    for (int i = 0; i < INSTRUCTION; ++i) //Imprime op1 en binario
      cout << op1.read().range(INSTRUCTION-(i+1),INSTRUCTION-(i+1));
    cout << " | " << setw(2);

    for (int i = 0; i < INSTRUCTION; ++i) //Imprime op2 en binario
      cout << op2.read().range(INSTRUCTION-(i+1),INSTRUCTION-(i+1));
    cout << " |" << setw(2);

    for (int i = 0; i < INSTRUCTION; ++i) //Imprime res en binario
      cout<< res.read().range(INSTRUCTION-(i+1),INSTRUCTION-(i+1));
    cout << " | " << setw(4);

    cout << instruction.read();//Imprime la instrucciones en decimal
    cout << setw (8) << "|   ";

    switch(instruction.read())
    {
      case 1: cout << "ADD"; break;
      case 2: cout << "SUB"; break;
      case 3: cout << "MUL"; break;
      case 4: cout << "DIV"; break;
      case 5: cout << "LOAD"; break;
      case 6: cout << "STORE"; break;
      default: cout << "Por definir"; break;
    }
    cout << endl;
  }


  void test()
  {
    cout << "\nInstrucción|  Op1  |  Op2  | Res  | Decimal | Operación\n"
         << "---------------------------------------------------------\n";

    for (int i = 0; i < INSTRUCTIONS; ++i)
    {
      wait();
      print();
    }
    
    sc_stop();
  }

  SC_CTOR(Testbench)
  {
    SC_THREAD(test);
    sensitive << clk.neg();
  }
};

#endif
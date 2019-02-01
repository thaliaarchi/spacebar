#include "parser.h"
#include "instruction.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: spacebar [file]\n";
    return 1;
  }

  std::ifstream in(argv[1]);
  Parser parser(in);

  try {
    Instruction instr;
    while (parser.next(instr)) {
      instr.printAsm(std::cout);
      std::cout << "\n";
    }
  }
  catch (const char* ex) {
    std::cerr << ex << "\n";
  }

  return 0;
}

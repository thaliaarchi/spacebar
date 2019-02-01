#ifndef WS_INSTRUCTION_H_
#define WS_INSTRUCTION_H_

#include "position.h"

#include <ostream>
#include <string>

enum class InstrType {
  PUSH,   DUP,    COPY,   SWAP,   DROP,   SLIDE,
  ADD,    SUB,    MUL,    DIV,    MOD,
  STORE,  RETRIEVE,
  LABEL,  CALL,   JMP,    JZ,     JN,     RET,    END,
  PRINTC, PRINTI, READC,  READI
};

std::ostream& operator<<(std::ostream& out, const InstrType& type);

struct Instruction {
  Instruction(InstrType type, const Position& position, int param = 0);
  Instruction();

  InstrType type;
  int param;
  Position position;

  std::ostream& printWS(std::ostream& out);
  std::ostream& printAsm(std::ostream& out);
  std::string paramToWs(bool is_signed);
};

#endif

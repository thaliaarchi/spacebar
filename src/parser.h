#ifndef WS_PARSER_H_
#define WS_PARSER_H_

#include "lexer.h"
#include "instruction.h"
#include "token.h"

class Parser {
public:
  Parser(Lexer&& lexer);

  bool next(Instruction& instr);

private:
  Lexer lexer_;
  Token instr_start_;

  Token nextToken();
  Instruction parseStack();
  Instruction parseArith();
  Instruction parseHeap();
  Instruction parseFlow();
  Instruction parseIO();
  int parseNumber();
  int parseLabel();
  Instruction instr(InstrType type, int param = 0) const;
};

#endif

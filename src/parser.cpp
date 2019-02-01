#include "parser.h"
#include "lexer.h"

Parser::Parser(Lexer&& lexer)
  : lexer_(lexer) {}

bool Parser::next(Instruction& instr) {
  if (!lexer_.next(instr_start_)) {
    return false;
  }
  switch (instr_start_.type) {
    case TokenType::SPACE: instr = parseStack(); return true;
    case TokenType::TAB:
      switch (nextToken().type) {
        case TokenType::SPACE: instr = parseArith(); return true;
        case TokenType::TAB: instr = parseHeap(); return true;
        case TokenType::LF: instr = parseIO(); return true;
      }
    case TokenType::LF: instr = parseFlow(); return true;
  }
  return false;
}

Token Parser::nextToken() {
  Token token;
  if (!lexer_.next(token)) {
    throw "Unexpected end of input";
  }
  return token;
}

Instruction Parser::parseStack() {
  switch (nextToken().type) {
    case TokenType::SPACE: return instr(InstrType::PUSH, parseNumber());
    case TokenType::TAB:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::COPY, parseNumber());
        case TokenType::TAB: throw "Invalid instruction";
        case TokenType::LF: return instr(InstrType::SLIDE, parseNumber());
      }
    case TokenType::LF:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::DUP);
        case TokenType::TAB: return instr(InstrType::SWAP);
        case TokenType::LF: return instr(InstrType::DROP);
      }
  }
  throw "Invalid instruction";
}

Instruction Parser::parseArith() {
  switch (nextToken().type) {
    case TokenType::SPACE:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::ADD);
        case TokenType::TAB: return instr(InstrType::SUB);
        case TokenType::LF: return instr(InstrType::MUL);
      }
    case TokenType::TAB:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::DIV);
        case TokenType::TAB: return instr(InstrType::MOD);
        case TokenType::LF: throw "Invalid instruction";
      }
    case TokenType::LF: throw "Invalid instruction";
  }
  throw "Invalid instruction";
}

Instruction Parser::parseHeap() {
  switch (nextToken().type) {
    case TokenType::SPACE: return instr(InstrType::STORE);
    case TokenType::TAB: return instr(InstrType::RETRIEVE);
    case TokenType::LF: throw "Invalid instruction";
  }
  throw "Invalid instruction";
}

Instruction Parser::parseFlow() {
  switch (nextToken().type) {
    case TokenType::SPACE:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::LABEL, parseLabel());
        case TokenType::TAB: return instr(InstrType::CALL, parseLabel());
        case TokenType::LF: return instr(InstrType::JMP, parseLabel());
      }
    case TokenType::TAB:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::JZ, parseLabel());
        case TokenType::TAB: return instr(InstrType::JN, parseLabel());
        case TokenType::LF: return instr(InstrType::RET);
      }
    case TokenType::LF:
      switch (nextToken().type) {
        case TokenType::SPACE:
        case TokenType::TAB: throw "Invalid instruction";
        case TokenType::LF: return instr(InstrType::END);
      }
  }
  throw "Invalid instruction";
}

Instruction Parser::parseIO() {
  switch (nextToken().type) {
    case TokenType::SPACE:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::PRINTC);
        case TokenType::TAB: return instr(InstrType::PRINTI);
        case TokenType::LF: throw "Invalid instruction";
      }
    case TokenType::TAB:
      switch (nextToken().type) {
        case TokenType::SPACE: return instr(InstrType::READC);
        case TokenType::TAB: return instr(InstrType::READI);
        case TokenType::LF: throw "Invalid instruction";
      }
    case TokenType::LF: throw "Invalid instruction";
  }
  throw "Invalid instruction";
}

int Parser::parseNumber() {
  switch (nextToken().type) {
    case TokenType::SPACE: return parseLabel();
    case TokenType::TAB: return -1 * parseLabel();
    case TokenType::LF: return 0;
  }
  return 0;
}

int Parser::parseLabel() {
  int number = 0;
  while (true) {
    switch (nextToken().type) {
      case TokenType::SPACE: number <<= 1; continue;
      case TokenType::TAB: number = (number << 1) + 1; continue;
      case TokenType::LF: return number;
    }
  }
}

Instruction Parser::instr(InstrType type, int param) const {
  return Instruction(type, instr_start_.position, param);
}

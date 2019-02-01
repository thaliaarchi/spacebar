#include "instruction.h"

#include <ostream>
#include <string>

Instruction::Instruction(InstrType type, const Position& position, int param)
  : type(type), param(param), position(position) {}
Instruction::Instruction()
  : type(InstrType::PUSH), position(Position(0, 0)) {}

std::ostream& operator<<(std::ostream& out, const InstrType& type) {
  switch (type) {
    case InstrType::PUSH:     return out << "PUSH";
    case InstrType::DUP:      return out << "DUP";
    case InstrType::COPY:     return out << "COPY";
    case InstrType::SWAP:     return out << "SWAP";
    case InstrType::DROP:     return out << "DROP";
    case InstrType::SLIDE:    return out << "SLIDE";
    case InstrType::ADD:      return out << "ADD";
    case InstrType::SUB:      return out << "SUB";
    case InstrType::MUL:      return out << "MUL";
    case InstrType::DIV:      return out << "DIV";
    case InstrType::MOD:      return out << "MOD";
    case InstrType::STORE:    return out << "STORE";
    case InstrType::RETRIEVE: return out << "RETRIEVE";
    case InstrType::LABEL:    return out << "LABEL";
    case InstrType::CALL:     return out << "CALL";
    case InstrType::JMP:      return out << "JMP";
    case InstrType::JZ:       return out << "JZ";
    case InstrType::JN:       return out << "JN";
    case InstrType::RET:      return out << "RET";
    case InstrType::END:      return out << "END";
    case InstrType::PRINTC:   return out << "PRINTC";
    case InstrType::PRINTI:   return out << "PRINTI";
    case InstrType::READC:    return out << "READC";
    case InstrType::READI:    return out << "READI";
    default:                  return out << "INVALID";
  }
}

std::ostream& Instruction::printWS(std::ostream& out) {
  switch (type) {
    case InstrType::PUSH:     return out << "  " << paramToWs(true);
    case InstrType::DUP:      return out << " \n ";
    case InstrType::COPY:     return out << " \t " << paramToWs(true);
    case InstrType::SWAP:     return out << " \n\t";
    case InstrType::DROP:     return out << " \n\n";
    case InstrType::SLIDE:    return out << " \t\n" << paramToWs(true);
    case InstrType::ADD:      return out << "\t   ";
    case InstrType::SUB:      return out << "\t  \t";
    case InstrType::MUL:      return out << "\t  \n";
    case InstrType::DIV:      return out << "\t \t ";
    case InstrType::MOD:      return out << "\t \t\t";
    case InstrType::STORE:    return out << "\t\t ";
    case InstrType::RETRIEVE: return out << "\t\t\t";
    case InstrType::LABEL:    return out << "\n  " << paramToWs(false);
    case InstrType::CALL:     return out << "\n \t" << paramToWs(false);
    case InstrType::JMP:      return out << "\n \n" << paramToWs(false);
    case InstrType::JZ:       return out << "\n\t " << paramToWs(false);
    case InstrType::JN:       return out << "\n\t\t" << paramToWs(true);
    case InstrType::RET:      return out << "\n\t\n";
    case InstrType::END:      return out << "\n\n\n";
    case InstrType::PRINTC:   return out << "\t\n  ";
    case InstrType::PRINTI:   return out << "\t\n \t";
    case InstrType::READC:    return out << "\t\n\t ";
    case InstrType::READI:    return out << "\t\n\t\t";
    default:                  return out << "[INVALID]";
  }
}

std::ostream& Instruction::printAsm(std::ostream& out) {
  switch (type) {
    case InstrType::PUSH:     return out << "\tpush " << param;
    case InstrType::DUP:      return out << "\tdup";
    case InstrType::COPY:     return out << "\tcopy " << param;
    case InstrType::SWAP:     return out << "\tswap";
    case InstrType::DROP:     return out << "\tdrop";
    case InstrType::SLIDE:    return out << "\tslide " << param;
    case InstrType::ADD:      return out << "\tadd";
    case InstrType::SUB:      return out << "\tsub";
    case InstrType::MUL:      return out << "\tmul";
    case InstrType::DIV:      return out << "\tdiv";
    case InstrType::MOD:      return out << "\tmod";
    case InstrType::STORE:    return out << "\tstore";
    case InstrType::RETRIEVE: return out << "\tretrieve";
    case InstrType::LABEL:    return out << "label_" << param << ":";
    case InstrType::CALL:     return out << "\tcall label_" << param;
    case InstrType::JMP:      return out << "\tjmp label_" << param;
    case InstrType::JZ:       return out << "\tjz label_" << param;
    case InstrType::JN:       return out << "\tjn label_" << param;
    case InstrType::RET:      return out << "\tret";
    case InstrType::END:      return out << "\tend";
    case InstrType::PRINTC:   return out << "\tprintc";
    case InstrType::PRINTI:   return out << "\tprinti";
    case InstrType::READC:    return out << "\treadc";
    case InstrType::READI:    return out << "\treadi";
    default:                  return out << "INVALID";
  }
}

std::string Instruction::paramToWs(bool is_signed) {
  std::string str;
  if (is_signed) {
    str = param >= 0 ? ' ' : '\t';
  }
  int p = param >= 0 ? param : -param;
  while (p > 0) {
    str = (p & 1 ? '\t' : ' ') + str;
    p >>= 1;
  }
  return str;
}

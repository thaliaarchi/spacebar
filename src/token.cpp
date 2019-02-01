#include "token.h"

#include <ostream>

std::ostream& operator<<(std::ostream& out, const TokenType& type) {
  switch (type) {
    case TokenType::SPACE: return out << "SPACE";
    case TokenType::TAB:   return out << "TAB";
    case TokenType::LF:    return out << "LF";
  }
  return out;
}

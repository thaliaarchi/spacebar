#include "lexer.h"
#include "token.h"

#include <fstream>

Lexer::Lexer(std::ifstream& in)
  : in_(in) {}

bool Lexer::next(Token& token) {
  char c;
  while (true) {
    if (!in_.get(c)) {
      return false;
    }
    position_.column++;
    switch (c) {
      case ' ': token = Token(TokenType::SPACE, position_); return true;
      case '\t': token = Token(TokenType::TAB, position_); return true;
      case '\n':
        token = Token(TokenType::LF, position_);
        position_.line++;
        position_.column = 0;
        return true;
    }
  }
}

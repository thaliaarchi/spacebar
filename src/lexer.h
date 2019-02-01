#ifndef WS_LEXER_H_
#define WS_LEXER_H_

#include "token.h"
#include "position.h"

#include <fstream>

class Lexer {
public:
  Lexer(std::ifstream& in);

  bool next(Token& token);

private:
  std::ifstream& in_;
  Position position_ = Position(1, 0);
};

#endif

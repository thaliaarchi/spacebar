#ifndef WS_TOKEN_H_
#define WS_TOKEN_H_

#include "position.h"

#include <ostream>

enum class TokenType {
  SPACE,
  TAB,
  LF
};

std::ostream& operator<<(std::ostream& out, const TokenType& type);

struct Token {
  Token(TokenType type, const Position& position)
    : type(type), position(position) {}
  Token()
    : type(TokenType::SPACE), position(Position(0, 0)) {}

  TokenType type;
  Position position;
};

#endif

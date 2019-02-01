#ifndef WS_POSITION_H_
#define WS_POSITION_H_

struct Position {
  Position(int line, int column)
    : line(line), column(column) {}

  int line;
  int column;
};

#endif

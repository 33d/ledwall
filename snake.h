#ifndef SNAKE_H_
#define SNAKE_H_

#include "pattern.h"

class Snake: public Pattern {
  typedef enum { RIGHT = 0x0, LEFT = 0x03, DOWN = 0x01, UP = 0x02 } Direction;

  struct dot {
    int8_t x, y;
  };

  static const int length = 10;
  struct dot dots[length];
  Direction direction;
  uint8_t head_dot;
  void plot(uint8_t x, uint8_t y, uint8_t c);
  void change_direction(dot* head);
public:
  Snake(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : Pattern(pixels, cols, rows), direction(RIGHT), head_dot(0) {}
  void init();
  void step();
  virtual ~Snake() {};
};

#endif /* MATRIX_H_ */

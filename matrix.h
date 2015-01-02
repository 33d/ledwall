/*
 * matrix.h
 *
 *  Created on: 30 Dec 2014
 *      Author: damien
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "pattern.h"

class Matrix: public Pattern {
  struct dot {
    uint8_t x, y;
    uint8_t val;
    uint8_t speed;
    uint32_t color;
  };

  static const int dot_count = 20;
  struct dot dots[dot_count];
  void init_dot(struct dot* d);
  void fade();
public:
  Matrix(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : Pattern(pixels, cols, rows) {}
  void init();
  bool step();
  virtual ~Matrix() {};
};

#endif /* MATRIX_H_ */

#include "matrix.h"
#include <string.h>

void Matrix::init() {
  memset(dots, 0, sizeof(dots));
  for (dot* d = dots; d < dots+dot_count; d++)
    init_dot(d);
}

void Matrix::init_dot(struct dot* d) {
  uint8_t seed = random();
  d->x = seed % cols;
  d->y = (d->x & 1) ? (rows-1) : 0;
  d->speed = seed & 0x07 << 3;
  d->val = 0;
  d->color = 0x00AAFF00;
  pixels.setPixelColor(((uint16_t) d->x * rows) + d->y, d->color);
}

void Matrix::fade() {
  uint8_t* p = pixels.getPixels();
  for (uint16_t i = 0; i < (uint16_t) rows*cols*3; i++)
    if (p[i] > 0)
      --p[i];
}

void Matrix::step() {
  delay(5);
  fade();

  for (dot* d = dots; d < dots+rows; d++) {
    // Does this dot need initializing?
    if (d->speed == 0)
      init_dot(d);
    // Does this dot need moving?
    if (d->val == d->speed) {
      bool reset = false;
      if (d->x & 1) {
        // Odd row, decrement y
        if (d->y == 0)
          reset = true;
        else
          --d->y;
      } else {
        if (d->y == rows - 1)
          reset = true;
        else
          ++d->y;
      }
      if (reset)
        d->speed = 0;
      else {
        d->val = 0;
        pixels.setPixelColor(((uint16_t) d->x * rows) + d->y, d->color);
      }
    } else
      ++d->val;
  }
}

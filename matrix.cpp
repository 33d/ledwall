#include "Adafruit_NeoPixel.h"
#include <string.h>
#include <stdint.h>

#define PIN 6
#define ROWS 8
#define COLS 12
#define DOTS 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ROWS*COLS, PIN, NEO_GRB + NEO_KHZ800);

struct dot {
  uint8_t x, y;
  uint8_t val;
  uint8_t speed;
  uint32_t color;
};
struct dot dots[DOTS];

const uint32_t colors[] = { 
  0x00FF0000, 0x0000FF00, 
  0x00FFFFFF, 0x00770077
};

void init_dot(struct dot* d) {
  uint8_t seed = random();
  d->x = seed % COLS;
  d->y = (d->x & 1) ? (ROWS-1) : 0;
  d->speed = seed & 0x07 << 3;
  d->val = 0;
  d->color = colors[(seed>>3) % 4];
  pixels.setPixelColor(((uint16_t) d->x * ROWS) + d->y, d->color);
}

void setup() {
  memset(dots, 0, sizeof(dots));
  pixels.begin();
  pixels.show();
  
  for (dot* d = dots; d < dots+DOTS; d++)
    init_dot(d);
}

void fade() {
  uint8_t* p = pixels.getPixels();
  for (uint16_t i = 0; i < ROWS*COLS*3; i++)
    if (p[i] > 0)
      --p[i];
}

void loop() {
  for (dot* d = dots; d < dots+DOTS; d++) {
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
        if (d->y == ROWS - 1)
          reset = true;
        else
          ++d->y;
      }
      if (reset)
        d->speed = 0;
      else {
        d->val = 0;
        pixels.setPixelColor(((uint16_t) d->x * ROWS) + d->y, d->color);
      }
    } else
      ++d->val;
  }

  pixels.show();
  fade();
  delay(5);
}


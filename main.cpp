#include "Adafruit_NeoPixel.h"
#include "matrix.h"
#include "snake.h"
#include <string.h>
#include <stdint.h>

#define PIN 6
#define ROWS 8
#define COLS 12
#define DOTS 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ROWS*COLS, PIN, NEO_GRB + NEO_KHZ800);

Pattern *effect;

void setup() {
  pixels.begin();
  pixels.show();

  effect = new Snake(pixels, COLS, ROWS);
  effect->init();
}

void loop() {
  effect->step();
  pixels.show();
}


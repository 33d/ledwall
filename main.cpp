#include "Adafruit_NeoPixel.h"
#include "matrix.h"
#include "snake.h"
#include <string.h>
#include <stdint.h>

#define PIN 6
#define ROWS 8
#define COLS 12
#define DOTS 20

#define EFFECT_TIME (300 * 1000)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ROWS*COLS, PIN, NEO_GRB + NEO_KHZ800);

Pattern *effect;
unsigned long last_change;

void next_effect() {
  static uint8_t id = 0;
  delete effect;
  pixels.clear();
  switch (id) {
  case 0: effect = new Snake(pixels, COLS, ROWS); break;
  case 1: effect = new Matrix(pixels, COLS, ROWS); break;
  }
  effect->init();
  id = ++id % 2;
}

void setup() {
  pixels.begin();
  pixels.show();

  next_effect();
  effect = new Snake(pixels, COLS, ROWS);
  effect->init();

  last_change = millis();
}

void loop() {
  if (millis() - last_change > EFFECT_TIME) {
    next_effect();
    last_change = millis();
  }

  effect->step();
  pixels.show();
}

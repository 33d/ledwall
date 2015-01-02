#include "Adafruit_NeoPixel.h"
#include "matrix.h"
#include "snake.h"
#include "scroll.h"
#include <string.h>
#include <stdint.h>

#define PIN 6
#define ROWS 8
#define COLS 12
#define DOTS 20

#define EFFECT_TIME ((uint32_t) 300 * 1000)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ROWS*COLS, PIN, NEO_GRB + NEO_KHZ800);

Pattern *effect;
unsigned long last_change;
bool cont;

void next_effect() {
  static uint8_t id = 0;
  delete effect;
  pixels.clear();
  switch (id) {
  case 0: effect = new Scroll(pixels, COLS, ROWS); break;
  case 1: effect = new Matrix(pixels, COLS, ROWS); break;
  case 2: effect = new Snake(pixels, COLS, ROWS); break;
  }
  effect->init();
  id = (id+1) % 3;
  cont = true;
}

void setup() {
  pixels.begin();
  pixels.show();

  next_effect();
  effect->init();

  last_change = millis();
}

void loop() {
  if (!cont || millis() - last_change > EFFECT_TIME) {
    next_effect();
    last_change = millis();
  }

  if (!effect->step())
    // the pattern doesn't want to continue
    cont = false;
  pixels.show();
}

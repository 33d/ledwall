#include "plasma.h"
#include <string.h>

// A loose port of
// http://demo-effects.cvs.sourceforge.net/viewvc/demo-effects/demo-effects/PLASMA/plasma.c?revision=1.5&view=markup

static int8_t isin(uint8_t x) {
  // [int((math.sin((x/16.0)*2*math.pi)/2)*256) for x in range(16)]
  static const int8_t isin_t[] = { 0, 48, 90, 118, 127, 118, 90, 48, 0, -48, -90, -118, -128, -118, -90, -48 };
  return isin_t[x / 16];
}

static const uint32_t colors[] = {
  0x062c00, 0x063400, 0x045200, 0x168600,
  0x66bc00, 0xffc81f, 0xff7019, 0xff3311,
  0xfc2400, 0xda2e00, 0x9a3894, 0x723bff,
  0x8275ff, 0x8db5ff, 0x8dffcb, 0x54ff11
};

void Plasma::init() {
}

bool Plasma::step() {
  delay(10);

  int8_t tpos1, tpos2, tpos3, tpos4;

  tpos4 = pos4;
  tpos3 = pos3;

  for (uint8_t i = 0; i < rows; i++) {
    tpos1 = pos1 + 20; //5;
    tpos2 = 12; //3;

    for (int j = 0; j < cols; j++) {
      int8_t x = ((int16_t) isin(tpos1) + isin(tpos2) + isin(tpos3) + isin(tpos4)) / 2;
      plot(j, i, colors[(128+x)>>4]);

      tpos1 += 15; // 5;
      tpos2 += 12; // 3;
    }

    tpos4 += 12; //3;
    tpos3 += 5; //1;
  }

  pos1 += 3; //9;
  pos3 += 2; //8;
  pos2 += 1;
  pos4 += 1;

  return true;
}

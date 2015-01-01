#include "snake.h"
#include "colors.h"
#include <string.h>
#include <stdio.h>

void Snake::init() {
  direction = DOWN;
  for (dot* d = dots + 1; d < dots+length; d++)
    d->x = -1;
  dots[0].x = 0;
  dots[0].y = 0;
  head_dot = 0;
}

void Snake::change_direction(dot* head) {
  Direction d;
  if (direction == UP || direction == DOWN) {
    if (head->x == 0)
      d = RIGHT;
    else if (head->x == cols-1)
      d = LEFT;
    else
      d = (random() & 1) ? LEFT : RIGHT;
  } else {
    if (head->y == 0)
      d = DOWN;
    else if (head->y == rows-1)
      d = UP;
    else
      d = (random() & 1) ? DOWN : UP;
  }
  direction = d;
}

void Snake::step() {
  delay(50);

  // Update the snake occasionally, otherwise just do the colours
  if (++loops > 4) {
    loops = 0;

    dot* head = &dots[head_dot];

    // Erase the last dot
    head_dot = (head_dot + 1) % length;
    dot* next = &dots[head_dot];
    if (next->x != -1)
      plot(next->x, next->y, 0);

    if ((direction == UP && head->y == 0)
        || (direction == DOWN && head->y == rows-1)
        || (direction == LEFT && head->x == 0)
        || (direction == RIGHT && head->x == cols-1)
        || ((random() & 0x09) == 0))
      change_direction(head);

    next->x = head->x;
    next->y = head->y;
    switch(direction) {
    case UP:        --next->y; break;
    case DOWN:    ++next->y; break;
    case LEFT:    --next->x; break;
    case RIGHT: ++next->x; break;
    }
  }

  // Plot the snake
  uint8_t i = head_dot;
  uint8_t c = head_color;
  do {
    dot* d = dots + i;
    plot(d->x, d->y, COLORS[c]);
    i = i == 0 ? length-1 : i-1;
    c = (c+1) % COLORS_COUNT;
  } while (i != head_dot);
  head_color = head_color == 0 ? (COLORS_COUNT - 1) : (head_color - 1);
}

#include "Arduino_LED_Matrix.h"

#define ROWS 8
#define COLS 12

uint8_t current_grid[ROWS][COLS] = { 0 };

uint8_t next_grid[ROWS][COLS] = { 0 };

uint8_t (*current)[COLS] = current_grid;
uint8_t (*next)[COLS] = next_grid;

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(9600);
  delay(1000);

  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (random(0, 100) < 30) {
        current_grid[y][x] = 1;
      }
    }
  }

  Serial.println("Conway's game of life on Arduino LED Matrix");
  matrix.begin();
}

void loop() {
  delay(200);

  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      int alive = 0;

      int left_x = x ? x - 1 : COLS - 1;
      int right_x = (x != COLS - 1) ? x + 1 : 0;
      int top_y = y ? y - 1 : ROWS - 1;
      int bottom_y = (y != ROWS - 1) ? y + 1 : 0;

      if (current[y][left_x] == 1)
        alive++;
      if (current[top_y][left_x] == 1)
        alive++;
      if (current[top_y][x] == 1)
        alive++;
      if (current[top_y][right_x] == 1)
        alive++;
      if (current[y][right_x] == 1)
        alive++;
      if (current[bottom_y][right_x] == 1)
        alive++;
      if (current[bottom_y][x] == 1)
        alive++;
      if (current[bottom_y][left_x] == 1)
        alive++;

      if (current[y][x] == 1) {
        if (alive < 2 || alive > 3)
          next[y][x] = 0;
        else
          next[y][x] = 1;
      } else {
        if (alive == 3)
          next[y][x] = 1;
        else
          next[y][x] = 0;
      }
    }
  }

  uint8_t(*tmp)[COLS] = current;
  current = next;
  next = tmp;

  display_grid();
}

void display_grid(void) {
  matrix.renderBitmap(current, 8, 12);
}

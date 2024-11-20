#include "Arduino_LED_Matrix.h"

#define ROWS 8
#define COLS 12

uint8_t grid[ROWS][COLS];

uint8_t current_grid[ROWS * COLS] = { 0 };
uint8_t next_grid[ROWS * COLS] = { 0 };

uint8_t *current = current_grid;
uint8_t *next = next_grid;

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(9600);
  delay(1000);

  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (random(0, 100) < 30) {
        current_grid[y * ROWS + x] = 1;
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

      if (current[y * COLS + left_x])
        alive++;
      if (current[top_y * COLS + left_x])
        alive++;
      if (current[top_y * COLS + x])
        alive++;
      if (current[top_y * COLS + right_x])
        alive++;
      if (current[y * COLS + right_x])
        alive++;
      if (current[bottom_y * COLS + right_x])
        alive++;
      if (current[bottom_y * COLS + x])
        alive++;
      if (current[bottom_y * COLS + left_x])
        alive++;

      if (current[y * COLS + x]) {
        if (alive < 2 || alive > 3)
          next[y * COLS + x] = false;
        else
          next[y * COLS + x] = true;
      } else {
        if (alive == 3)
          next[y * COLS + x] = true;
        else
          next[y * COLS + x] = false;
      }
    }
  }

  uint8_t *tmp = current;
  current = next;
  next = tmp;

  display_grid();
}

void display_grid(void) {
  for (int x = 0; x < COLS; x++)
    for (int y = 0; y < ROWS; y++)
      grid[y][x] = current[y * ROWS + x];


  matrix.renderBitmap(grid, 8, 12);
}
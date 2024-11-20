#include <cstdint>

#include <raylib.h>

#define ROWS 8
#define COLS 12
#define WIDTH 100
#define HEIGHT WIDTH

uint8_t current_grid[ROWS][COLS] = { 0 };

uint8_t next_grid[ROWS][COLS] = { 0 };

uint8_t (*current)[COLS] = current_grid;
uint8_t (*next)[COLS] = next_grid;

int
main(void)
{
	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < ROWS; y++) {
			current_grid[y][x] = GetRandomValue(0, 10) < 3 ? 1 : 0;
			next_grid[y][x] = false;
		}
	}

	InitWindow(COLS * WIDTH, ROWS * HEIGHT, "GameOfLife");

	SetTargetFPS(5);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int x = 0; x < COLS; x++) {
			for (int y = 0; y < ROWS; y++) {
				uint8_t cell = current[y][x];

				if (cell)
					DrawRectangle(x * WIDTH, y * HEIGHT, WIDTH, HEIGHT, RED);

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

				if (cell == 1) {
					if (alive < 2 || alive > 3)
						next[y][x] = false;
					else
						next[y][x] = true;
				} else {
					if (alive == 3)
						next[y][x] = true;
					else
						next[y][x] = false;
				}
			}
		}

		uint8_t(*tmp)[COLS] = current;
		current = next;
		next = tmp;

		for (int x = 0; x < COLS - 1; x++)
			DrawLine(x * WIDTH + WIDTH, 0, x * WIDTH + WIDTH, ROWS * HEIGHT, BLACK);

		for (int y = 0; y < ROWS - 1; y++)
			DrawLine(0, y * HEIGHT + HEIGHT, COLS * WIDTH, y * HEIGHT + HEIGHT, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

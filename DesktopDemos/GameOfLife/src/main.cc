#include <iostream>

#include <raylib.h>

#define ROWS 8
#define COLS 12
#define WIDTH 100
#define HEIGHT WIDTH

int
main(void)
{
	bool* current = new bool[ROWS * COLS];
	bool* next = new bool[ROWS * COLS];

	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < ROWS; y++) {
			current[y * COLS + x] = GetRandomValue(0, 10) < 3 ? true : false;
			next[y * COLS + x] = false;
		}
	}

	InitWindow(COLS * WIDTH, ROWS * HEIGHT, "GameOfLife");

	SetTargetFPS(10);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int x = 0; x < COLS; x++) {
			for (int y = 0; y < ROWS; y++) {
				bool cell = current[y * COLS + x];

				if (cell)
					DrawRectangle(x * WIDTH, y * HEIGHT, WIDTH, HEIGHT, RED);

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

				if (cell) {
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

		bool* tmp = current;
		current = next;
		next = tmp;

		for (int x = 0; x < COLS - 1; x++)
			DrawLine(x * WIDTH + WIDTH, 0, x * WIDTH + WIDTH, ROWS * HEIGHT, BLACK);

		for (int y = 0; y < ROWS - 1; y++)
			DrawLine(0, y * HEIGHT + HEIGHT, COLS * WIDTH, y * HEIGHT + HEIGHT, BLACK);

		EndDrawing();
	}

	CloseWindow();

	delete[] current;
	delete[] next;

	return 0;
}

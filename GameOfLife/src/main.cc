#include <iostream>

#include <raylib.h>

#define ROWS 8
#define COLS 12
#define WIDTH 100
#define HEIGHT WIDTH

bool current_grid[ROWS * COLS];
bool next_grid[ROWS * COLS];

int
main(void)
{
	for (int i = 0; i < ROWS * COLS; i++) {
		current_grid[i] = GetRandomValue(0, 1) ? true : false;
		next_grid[i] = false;
	}

	InitWindow(COLS * WIDTH, ROWS * HEIGHT, "GameOfLife");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int i = 0; i < ROWS * COLS; i++) {
			int x = i % 12;
			int y = i / 12;

			bool cell = current_grid[i];
			next_grid[i] = !cell;

			if (cell)
				DrawRectangle(x * WIDTH, y * HEIGHT, WIDTH, HEIGHT, RED);
		}

		for (int x = 0; x < COLS - 1; x++)
			DrawLine(x * WIDTH + WIDTH, 0, x * WIDTH + WIDTH, ROWS * HEIGHT, BLACK);

		for (int y = 0; y < ROWS - 1; y++)
			DrawLine(0, y * HEIGHT + HEIGHT, COLS * WIDTH, y * HEIGHT + HEIGHT, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

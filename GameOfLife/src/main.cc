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

	for (int i = 0; i < ROWS * COLS; i++) {
		current[i] = GetRandomValue(0, 1) ? true : false;
		next[i] = false;
	}

	InitWindow(COLS * WIDTH, ROWS * HEIGHT, "GameOfLife");

	SetTargetFPS(1);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int i = 0; i < ROWS * COLS; i++) {
			int x = i % 12;
			int y = i / 12;

			bool cell = current[i];
			next[i] = !cell;

			if (cell)
				DrawRectangle(x * WIDTH, y * HEIGHT, WIDTH, HEIGHT, RED);
		}

		for (int x = 0; x < COLS - 1; x++)
			DrawLine(x * WIDTH + WIDTH, 0, x * WIDTH + WIDTH, ROWS * HEIGHT, BLACK);

		for (int y = 0; y < ROWS - 1; y++)
			DrawLine(0, y * HEIGHT + HEIGHT, COLS * WIDTH, y * HEIGHT + HEIGHT, BLACK);

		EndDrawing();

		bool* tmp = current;
		current = next;
		next = tmp;
	}

	CloseWindow();

	delete[] current;
	delete[] next;

	return 0;
}

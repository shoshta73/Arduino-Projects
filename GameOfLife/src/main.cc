#include <raylib.h>

#define ROWS 8
#define COLS 12
#define WIDTH 100
#define HEIGHT WIDTH

int
main(void)
{
	InitWindow(COLS * WIDTH, ROWS * HEIGHT, "GameOfLife");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		for (int x = 0; x < COLS - 1; x++)
			DrawLine(x * WIDTH + WIDTH + 1, 0, x * WIDTH + WIDTH + 1, ROWS * HEIGHT, BLACK);

		for (int y = 0; y < ROWS - 1; y++)
			DrawLine(0, y * HEIGHT + HEIGHT + 1, COLS * WIDTH, y * HEIGHT + HEIGHT + 1, BLACK);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

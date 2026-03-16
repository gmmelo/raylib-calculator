#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#include <stdio.h>

int main() {
	const int LABEL_SIZE = 100;
	const int screen_width = 400;
	const int screen_height = 600;

	int btn_pressed = 0;
	Vector2 mouse_cell = { 0 };
	char label_str[LABEL_SIZE] = "Welcome to the calculator.";


	InitWindow(screen_width, screen_height, "gml - raylib calculator");	
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			int grid_width = screen_width - 100;
			int grid_hmargin = (screen_width - grid_width) / 2;
			int grid_vmargin_top = 200;
			int grid_vmargin_bot = 100;
			int grid_height = screen_height - (grid_vmargin_top + grid_vmargin_bot);
			int grid_cell_hcount = 3;
			GuiGrid((Rectangle) { grid_hmargin, grid_vmargin_top, grid_width, grid_height },
				NULL, grid_width / grid_cell_hcount, 1, &mouse_cell);

			int btn_pressed = GuiButton((Rectangle){100, 520, screen_width - 200, screen_height - 540}, "Button") ^ btn_pressed;

			if (btn_pressed)
			{
				snprintf(label_str, LABEL_SIZE, "%f %f", mouse_cell.x, mouse_cell.y);
				DrawText(label_str, 100, 50, 16, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
			}

		EndDrawing();
	}	
}

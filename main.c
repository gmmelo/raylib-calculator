#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#include <stdio.h>


// ===========================
// GUI Constants
const int LABEL_SIZE = 100;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;
// ===========================


// ===========================
// Forward Declarations
void draw_gui();
void setup_number_grid();
// ===========================


typedef enum {
	FIRST_INPUT,
	SECOND_INPUT,
	SHOW_RESULT
} CalculationStage;


typedef enum {
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
} Operation;


typedef struct {
	char label_str[LABEL_SIZE];
} GuiData;


typedef struct {
	GuiData gui_data;
	CalculationStage stage;
	Operation operation;
	int first_num;
	int second_num;
	int result;
} AppContext;


int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gml - raylib calculator");	
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		draw_gui();
	}	
}


void draw_gui() {
	BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		setup_number_grid();
		DrawText("Hello!", 100, 50, 16, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
	EndDrawing();
}


void setup_number_grid() {
	int grid_width = SCREEN_WIDTH - 100;
	int grid_hmargin = (SCREEN_WIDTH - grid_width) / 2;
	int grid_vmargin_top = 200;
	int grid_vmargin_bot = 100;
	int grid_height = SCREEN_HEIGHT - (grid_vmargin_top + grid_vmargin_bot);
	int grid_cell_hcount = 3;
	int grid_cell_vcount = 3;
	int grid_cell_width = grid_width / grid_cell_hcount;
	int grid_cell_height = grid_height / grid_cell_vcount;
	int grid_cell_padding = 2;

	for (int i = 0; i < 9; i++) {
		int y = i / grid_cell_hcount;
		int x = i % grid_cell_hcount;
		int num = i + 1;

		char num_label[2] = { 0 };
		snprintf(num_label, 2, "%d", num);

		int start_x = grid_hmargin + (grid_cell_width * x) + grid_cell_padding;
		int start_y = grid_vmargin_top + (grid_cell_height * y);

		GuiButton((Rectangle){ start_x, start_y, grid_cell_width - grid_cell_padding,
							   grid_cell_height - grid_cell_padding }, num_label);
	}
}

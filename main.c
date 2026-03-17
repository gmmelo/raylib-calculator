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


// ===========================
// Forward Declarations
void draw_gui(AppContext* ctx);
void setup_number_grid(AppContext* ctx);
void setup_last_row(int start_x, int start_y, int width, int height, int padding);
void setup_operation_row(int start_x, int start_y, int width, int height, int padding);
AppContext new_app_context();
AppContext* allocate_app_context();
void destroy_app_context(AppContext* ctx);
// ===========================


int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gml - raylib calculator");	
	SetTargetFPS(60);

	AppContext* ctx = allocate_app_context();

	while (!WindowShouldClose()) {
		draw_gui(ctx);
	}	

	destroy_app_context(ctx);
}


AppContext* allocate_app_context() {
	//GuiData gui = { .label_str = "Click a number to start input." };
	AppContext* ctx = (AppContext*) malloc(sizeof(AppContext));
	ctx->gui_data = (GuiData){ .label_str = "Hello!" };
	ctx->stage = FIRST_INPUT;
	return ctx;
}


void destroy_app_context(AppContext* ctx) {
	free(ctx);
}


void draw_gui(AppContext* ctx) {
	BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		setup_number_grid(ctx);
		DrawText(ctx->gui_data.label_str, 100, 50, 16, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
	EndDrawing();
}


void setup_number_grid(AppContext* ctx) {
	int grid_width = SCREEN_WIDTH - 40;
	int grid_hmargin = (SCREEN_WIDTH - grid_width) / 2;
	int grid_vmargin_top = 200;
	int grid_vmargin_bot = 110;
	int grid_height = SCREEN_HEIGHT - (grid_vmargin_top + grid_vmargin_bot);
	int grid_cell_hcount = 3;
	int grid_cell_vcount = 3;
	int grid_cell_width = grid_width / grid_cell_hcount;
	int grid_cell_height = grid_height / grid_cell_vcount;
	int grid_cell_padding = 2;

	setup_operation_row(grid_hmargin, grid_vmargin_top - 58, grid_width, grid_cell_height * 3 / 5, 2);

	// Set up 1-9 buttons
	for (int i = 0; i < 9; i++) {
		int y = i / grid_cell_hcount;
		int x = i % grid_cell_hcount;
		int num = i + 1;
		
		char label[10] = { 0 };
		snprintf(label, 2, "%d", num);

		int start_x = grid_hmargin + (grid_cell_width * x) + grid_cell_padding;
		int start_y = grid_vmargin_top + (grid_cell_height * y);

		if (GuiButton((Rectangle){ start_x, start_y, grid_cell_width - (grid_cell_padding * 2),
							   grid_cell_height - (grid_cell_padding * 2) }, label)) {
								snprintf(ctx->gui_data.label_str, LABEL_SIZE, "%d", i + 1);
							   }
	}

	int last_row_start_x = grid_hmargin;
	int last_row_start_y = grid_vmargin_top + (grid_cell_height * 3);
	setup_last_row(last_row_start_x, last_row_start_y, grid_width, grid_cell_height, grid_cell_padding);
}


void setup_operation_row(int start_x, int start_y, int width, int height, int padding) {
	int cell_width = width / 3;
	int btn_width = cell_width - (2 * padding);
	int btn_height = height - (2 * padding);

	GuiButton((Rectangle) { start_x + padding, start_y,
		btn_width, btn_height }, "+");
	GuiButton((Rectangle) { start_x + cell_width + padding, start_y,
		btn_width, btn_height }, "-");
	GuiButton((Rectangle) { start_x + (2 * cell_width) + padding, start_y,
		btn_width, btn_height / 2 - padding }, "*");
	GuiButton((Rectangle) { start_x + (2 * cell_width) + padding, start_y + btn_height / 2 + padding + 1,
		btn_width, btn_height / 2 - padding }, "/");
}


void setup_last_row(int start_x, int start_y, int width, int height, int padding) {
	int cell_width = width / 3;
	int btn_width = cell_width - (2 * padding);
	int btn_height = height - (2 * padding);

	GuiButton((Rectangle) { start_x + padding, start_y,
		btn_width, btn_height }, "DOT");
	GuiButton((Rectangle) { start_x + cell_width + padding, start_y,
		btn_width, btn_height }, "0");
	GuiButton((Rectangle) { start_x + (2 * cell_width) + padding, start_y,
		btn_width, btn_height }, "EQUALS");
}
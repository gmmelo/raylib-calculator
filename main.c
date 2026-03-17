#include <stdio.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "src/raygui.h"
#include "src/calc.h"
#include "src/main.h"


int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gml - raylib calculator");	
	SetTargetFPS(60);

	AppContext ctx = { 0 };
	ctx.display_str = malloc(sizeof(char) * DISPLAY_STR_SIZE);
	snprintf(ctx.display_str, DISPLAY_STR_SIZE, "Welcome to the calculator!");
	ctx.stage = FIRST_INPUT;

	while (!WindowShouldClose()) {
		draw_gui(&ctx);
	}

	free(ctx.display_str);
}


void draw_gui(AppContext* ctx) {
	BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		setup_math_display(ctx);
		setup_button_grid(ctx);
	EndDrawing();
}


void setup_math_display(AppContext* ctx) {
		DrawText(
			ctx->display_str,
			H_MARGIN,
			DISPLAY_BOX_HEIGHT/2,
			20,
			GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL))
		);
}


void setup_button_grid(AppContext* ctx) {
	const int grid_width = SCREEN_WIDTH - (H_MARGIN * 2);
	const int grid_height = SCREEN_HEIGHT - (V_MARGIN * 2) - DISPLAY_BOX_HEIGHT;
	const int grid_cols = 3;
	const int grid_rows = 5;
	const int grid_cell_width = grid_width / grid_cols;
	const int grid_cell_height = grid_height / grid_rows;

	for (int i = 0; i < grid_cols * grid_rows; i++) {
		int y = i / grid_cols;
		int x = i % grid_cols;

		Rectangle btn_dimensions = {
			.x = H_MARGIN + (x * grid_cell_width) + BTN_PADDING,
			.y = V_MARGIN + DISPLAY_BOX_HEIGHT + (y * grid_cell_height) + BTN_PADDING,
			.width = grid_cell_width - (BTN_PADDING * 2),
			.height = grid_cell_height - (BTN_PADDING * 2)
		};

		char label[DISPLAY_STR_SIZE];

		// Set-up 1-9 buttons
		if (i > 2 && i < 12) {
			int digit = i - 3;
			snprintf(label, DISPLAY_STR_SIZE, "%d", digit);
			if (GuiButton(
				btn_dimensions,
				label
			)) { append_digit(digit, ctx); }
			continue;
		}

		// Set-up top and bottom row
		Rectangle mult_dimensions = btn_dimensions;
		Rectangle div_dimensions = btn_dimensions;
		switch (i) {
			case 0: // Add Button
				if (GuiButton(
					btn_dimensions,
					"+"
				)) { start_operation(ADD, ctx); }
				break;

			case 1: // Subtract Button
				if (GuiButton(
					btn_dimensions,
					"-"
				)) { start_operation(SUBTRACT, ctx); }
				break;

			case 2: // Multiply & Divide Buttons
				mult_dimensions.height /= 2;
				mult_dimensions.height -= BTN_PADDING;
				div_dimensions.height /= 2;
				div_dimensions.height -= BTN_PADDING;
				div_dimensions.y += mult_dimensions.height + (2 * BTN_PADDING);
				
				if (GuiButton(
					mult_dimensions,
					"*"
				)) { start_operation(MULTIPLY, ctx); }

				if (GuiButton(
					div_dimensions,
					"/"
				)) { start_operation(DIVIDE, ctx); }

				break;

			case 12: // Decimal Button
				if (GuiButton(
					btn_dimensions,
					"."
				)) { make_decimal(ctx); }
				break;

			case 13: // Zero Button
				if (GuiButton(
					btn_dimensions,
					"0"
				)) { append_digit(0, ctx); }
				break;

			case 14: // Equals Button
				if (GuiButton(
					btn_dimensions,
					"="
				)) { calculate_result(ctx); }
				break;
		}
	}
}
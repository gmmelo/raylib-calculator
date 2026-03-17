#ifndef MAIN_H
#define MAIN_H

// GUI Constants
#define DISPLAY_STR_SIZE 100
static const int SCREEN_WIDTH = 400;
static const int SCREEN_HEIGHT = 600;
static const int H_MARGIN = 50;
static const int V_MARGIN = 50;
static const int BTN_PADDING = 2;
static const int DISPLAY_BOX_HEIGHT = 100;

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
	char* display_str;
	CalculationStage stage;
	Operation operation;
	char first_num[DISPLAY_STR_SIZE];
	char second_num[DISPLAY_STR_SIZE];
	char is_decimal;
} AppContext;

void draw_gui(AppContext* ctx);
void setup_math_display(AppContext* ctx);
void setup_button_grid(AppContext* ctx);

#endif // MAIN_H
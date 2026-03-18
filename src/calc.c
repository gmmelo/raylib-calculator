#include "main.h"
#include "calc.h"
#include <string.h>
#include <stdio.h>

void append_digit(char* digit, AppContext* ctx) {
    switch (ctx->stage) {
        case SHOW_RESULT:
            ctx->display_str[0] = 0;
            ctx->stage = FIRST_INPUT;
            ctx->is_decimal = 0;
        case FIRST_INPUT:
            snprintf(ctx->first_num, DISPLAY_STR_SIZE, "%s", digit);
            break;
        case SECOND_INPUT:
            snprintf(ctx->second_num, DISPLAY_STR_SIZE, "%s", digit);
            break;
    }

    snprintf(ctx->display_str, DISPLAY_STR_SIZE, "%s%s", ctx->display_str, digit);
}

void start_operation(Operation operation, AppContext* ctx) {
    switch(ctx->stage) {
        case FIRST_INPUT:
            ctx->stage = SECOND_INPUT;
            ctx->is_decimal = 0;
            break;
        case SECOND_INPUT:
            return;
        case SHOW_RESULT:
            snprintf(ctx->first_num, DISPLAY_STR_SIZE, "%s", ctx->display_str);
            ctx->stage = FIRST_INPUT;
            break;
    }
    
    switch (operation) {
        case ADD:
            snprintf(ctx->display_str, DISPLAY_STR_SIZE, "%s+", ctx->display_str);
            break;
        case SUBTRACT:
            snprintf(ctx->display_str, DISPLAY_STR_SIZE, "%s-", ctx->display_str);
            break;
        case MULTIPLY:
            snprintf(ctx->display_str, DISPLAY_STR_SIZE, "%s*", ctx->display_str);
            break;
        case DIVIDE:
            snprintf(ctx->display_str, DISPLAY_STR_SIZE, "%s/", ctx->display_str);
            break;
    }

    ctx->operation = operation;
}

void make_decimal(AppContext* ctx) {
    if (!ctx->is_decimal) {
        append_digit(".", ctx);
    }
    ctx->is_decimal = 1;
}

void calculate_result(AppContext* ctx) {
    // TODO: Implement number parsing logic
    ctx->display_str[0] = 0;
    ctx->stage = SHOW_RESULT;
}

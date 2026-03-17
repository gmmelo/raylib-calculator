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
            strlcpy(ctx->first_num, digit, DISPLAY_STR_SIZE);
            break;
        case SECOND_INPUT:
            strlcpy(ctx->second_num, digit, DISPLAY_STR_SIZE);
            break;
    }

    strlcat(ctx->display_str, digit, DISPLAY_STR_SIZE);
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
            strlcpy(ctx->first_num, ctx->display_str, DISPLAY_STR_SIZE);
            ctx->stage = FIRST_INPUT;
            break;
    }
    
    switch (operation) {
        case ADD:
            strlcat(ctx->display_str, "+", DISPLAY_STR_SIZE);
            break;
        case SUBTRACT:
            strlcat(ctx->display_str, "-", DISPLAY_STR_SIZE);
            break;
        case MULTIPLY:
            strlcat(ctx->display_str, "*", DISPLAY_STR_SIZE);
            break;
        case DIVIDE:
            strlcat(ctx->display_str, "/", DISPLAY_STR_SIZE);
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
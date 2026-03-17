#include "main.h"

#ifndef CALC_H
#define CALC_H

void append_digit(char* digit, AppContext* ctx);
void start_operation(Operation operation, AppContext* ctx);
void make_decimal(AppContext* ctx);
void calculate_result(AppContext* ctx);

#endif // CALC_H
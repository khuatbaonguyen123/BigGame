#include "Common.h"

Tetrimino tetrimino(const int *data, const int &side) {
    return {data,side};
}

int get_data_value(const int* values, const int width, const int row, const int col)
{
    int index = row * width + col;
    return values[index];
}

void set_data_value(int* values, const int width, const int row, const int col, const int value)
{
    int index = row * width + col;
    values[index] = value;
}
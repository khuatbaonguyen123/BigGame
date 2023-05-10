#include "common.h"

/***
    data: an array of matrix
    side: the side of matrix (length of data = side * side)
 ***/
Tetrimino tetrimino(const int *data, const int &side) {
    return {data,side};
}


/***
    data: an array of matrix
    width: the width of matrix
    row: the row location of the element we want to take value
    col: the column location of the element we want to take value
 ***/
int get_data_value(const int *data, const int &width, const int &row, const int&col)
{
    return data[width * row + col];
}


/***
    data: an array of matrix
    width: the width of matrix
    row: the row location of the element we want to take value
    col: the column location of the element we want to take value
    value: valuation we want to set for the element of matrix
 ***/
void set_data_value(int *data, const int &width, const int &row, const int&col, const int &value)
{
    data[width * row + col] = value;
}


/***
    min: the bottom of limitation
    max: the top of the limitation
 ***/
int get_random_number(const int &min, const int &max)
{
    return rand() % (max - min + 1) + min;
}


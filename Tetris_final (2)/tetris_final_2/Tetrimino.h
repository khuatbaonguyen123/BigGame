#ifndef TETRIMINO_H
#define TETRIMINO_H

class Tetrimino {
public:
    const int *data; //matrix of the tetrimino
    const int side;  //side of the tetrimino (length of data = side * side)

    /***
        return value of data's element
    ***/
    int tetrimino_get( const int& row, const int& col,
                        const int &rotation) const;

    //desturtor
    ~Tetrimino();
};

#endif //TETRIMINO_H

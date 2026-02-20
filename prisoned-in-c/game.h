#ifndef _GAME_H_
#define _GAME_H_

#include "sys/types.h"
#include "parameters.h"

struct aCell{
    float point;
    int memory;
    char (*strategy)();
};

typedef struct aCell Cell_str;
typedef struct aCell * Cell_ptr ;

struct CellMatrix
{
    Cell_ptr matrix[DIM][DIM];
    float proportion;
    int epoc;
};



typedef struct CellMatrix CellMat;
typedef struct CellMatrix * CellMatPtr ;

CellMatPtr halfMatrixCreator();

int neighborhoodApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col);

int oneRandNeighbourApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col);

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2);

u_int8_t * colorOfCell(Cell_ptr player);

#endif
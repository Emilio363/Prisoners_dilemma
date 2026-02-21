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

Cell_ptr ** halfMatrixCreator(ParamPtr par);

int neighborhoodApply(ParamPtr param,
    int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
    Cell_ptr ** Cells);

int _oneNeighborhoodApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells , int row, int col);

int randNeighbourApply(ParamPtr param,
    int (*fun)(Cell_ptr, Cell_ptr, ParamPtr), 
    Cell_ptr ** Cells);

int _oneRandNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells , int row, int col);

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

u_int8_t * colorOfCell(Cell_ptr player);

Cell_ptr ** halfMatrixCreator(ParamPtr param);

char (*_randomStrategy(void))(void);

Cell_ptr ** randMatrixCreator(ParamPtr param);

#endif
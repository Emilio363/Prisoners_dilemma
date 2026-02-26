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

int allMatrixPointZero(ParamPtr param, Cell_ptr ** Cells);

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

u_int8_t * colorOfCell(Cell_ptr player);

char (*_randomStrategy(void))(void);

Cell_ptr ** randMatrixCreator(ParamPtr param);

#endif
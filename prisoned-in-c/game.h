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

struct dataHolder{
    float points[6];
    int memories[6];
    int strategies[6];
};

typedef struct dataHolder Data_str;
typedef struct dataHolder * Data_ptr;

int allMatrixPointZero(ParamPtr param, Cell_ptr ** Cells);

int neighborhoodApply(ParamPtr param,
    int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
    Cell_ptr ** Cells);

int _oneNeighborhoodApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells , int row, int col);

int randNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr, float),
                    Cell_ptr ** Cells);

int _oneRandNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr, float),
                    Cell_ptr ** Cells , int row, int col, u_int32_t intrand);

int matrixSIRUpdate(int ** initial, int ** targhet, 
                SirParamPtr param);

int cellSIRUpdate(int row, int col, int ** initial, int ** targhet, 
                SirParamPtr param, int intrand);

u_int8_t * colorOfCell(Cell_ptr player);

Cell_ptr ** halfMatrixCreator(ParamPtr par);

Cell_ptr ** randMatrixCreator(ParamPtr param);

int ** intMatrixCreator(ParamPtr param);

int ** intMatrixPopulator(SirParamPtr param, int ** matrix);

#endif
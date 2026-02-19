#ifndef _GAME_H_
#define _GAME_H_

#include "sys/types.h"

#define T 1.05; //1<T<2 il guadagno ottenuto dal aver tradito l'avversario
#define R 1; // il guadagno dalla collaborazione
#define P 0; //il guadagno dal tradimento reciproco
#define S 0; //il guadagno se si viene traditi mentre si collabora

#define Max_memory 10
#define K 1.05
#define beta 0.5


struct aCell{
    float point;
    int memory;
    char (*strategy)();
};

typedef struct aCell Cell_str;
typedef struct aCell * Cell_ptr ;


int neighborhoodApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col);

int oneRandNeighbourApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col);

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2);

u_int8_t * colorOfCell(Cell_ptr player);

#endif
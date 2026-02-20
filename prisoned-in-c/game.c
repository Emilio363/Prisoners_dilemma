#include <stdio.h> // to debug
#include <stdlib.h>
#include "game.h"
#include "strategy.h"
#include "formulas.h" // to debug
#include "sys/types.h"
#include "parameters.h"

CellMatPtr cellMatCreator(){
    return (CellMatPtr)malloc(sizeof(CellMat));
}

CellMatPtr halfMatrixCreator(){
    CellMatPtr Cells = cellMatCreator();
    for(int i = 0; i<DIM; i++){
            for(int j = 0; j<DIM/2; j++ ){
                Cells->matrix[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
                Cells->matrix[i][j]->memory = 0;
                Cells->matrix[i][j]->point = 0;
                Cells->matrix[i][j]->strategy = cooperate;
            }
            for(int j = DIM/2; j<DIM; j++ ){
                Cells->matrix[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
                Cells->matrix[i][j]->memory = 0;
                Cells->matrix[i][j]->point = 0;
                Cells->matrix[i][j]->strategy = defect;
            }
        }
    return Cells;
    }

int neighborhoodApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    
    for (int dir = 0; dir < 4; dir++) {
        int nrow = row + dx[dir];
        int ncol = col + dy[dir];

        if (nrow >= 0 && nrow < dimension && ncol >= 0 && ncol < dimension) {
            //if (fun == changeStrategy){ printf("try to change strat\n");} // to debug
            fun(Cells[row][col], Cells[nrow][ncol]);
        }
    }
    return 0;
}

int oneRandNeighbourApply( int (*fun)(Cell_ptr, Cell_ptr),int dimension, Cell_ptr Cells[dimension][dimension] , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    int nrow;
    int ncol;

    do{
        int dir = rand()%4;
        nrow = row + dx[dir];
        ncol = col + dy[dir];
    }while(!(nrow >= 0 && nrow < dimension && ncol >= 0 && ncol < dimension));
    
    fun(Cells[row][col], Cells[nrow][ncol]);
    return 0;
}

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2){
    char move1 = player1->strategy();
    char move2 = player2->strategy();

    if ((move1 == 'C') && (move2 == 'C')) {
        return R;
    }
    else if ((move1 == 'C') && (move2 == 'D')) {
        return S;
    }
    else if ((move1 == 'D') && (move2 == 'C')) {
        return T;
    }
    else if ((move1 == 'D') && (move2 == 'D')) {
        return P;
    }
    else {
        return -1;
    }
}

// una funzione per trovare il colore della cella
u_int8_t * colorOfCell(Cell_ptr player){
    return strategyColor(player->strategy);
}
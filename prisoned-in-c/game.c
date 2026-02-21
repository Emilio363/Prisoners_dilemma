#include <stdio.h> // to debug
#include <stdlib.h>
#include "game.h"
#include "strategy.h"
#include "formulas.h" // to debug
#include "sys/types.h"
#include "parameters.h"

int neighborhoodApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    
    for (int dir = 0; dir < 4; dir++) {
        int nrow = row + dx[dir];
        int ncol = col + dy[dir];

        if (nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim) {
            //if (fun == changeStrategy){ printf("try to change strat\n");} // to debug
            fun(Cells[row][col], Cells[nrow][ncol], param);
        }
    }
    return 0;
}

int oneRandNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    int nrow;
    int ncol;

    do{
        int dir = rand()%4;
        nrow = row + dx[dir];
        ncol = col + dy[dir];
    }while(!(nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim));
    
    fun(Cells[row][col], Cells[nrow][ncol], param);
    return 0;
}

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2, ParamPtr param){
    char move1 = player1->strategy();
    char move2 = player2->strategy();

    if ((move1 == 'C') && (move2 == 'C')) {
        return param->r;
    }
    else if ((move1 == 'C') && (move2 == 'D')) {
        return param->s;
    }
    else if ((move1 == 'D') && (move2 == 'C')) {
        return param->t;
    }
    else if ((move1 == 'D') && (move2 == 'D')) {
        return param->p;
    }
    else {
        return -1;
    }
}

// una funzione per trovare il colore della cella
u_int8_t * colorOfCell(Cell_ptr player){
    return strategyColor(player->strategy);
}

Cell_ptr ** halfMatrixCreator(ParamPtr param){
    Cell_ptr ** Cells =(Cell_ptr**) malloc(param->dim * sizeof(Cell_ptr));

    for(int i = 0; i<param->dim; i++){
        Cells[i] = (Cell_ptr*) malloc(param->dim * sizeof(Cell_ptr));
        for(int j = 0; j<param->dim/2; j++ ){
            Cells[i][j] = (Cell_str *) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = cooperate;
        }
        for(int j = param->dim/2; j<param->dim; j++ ){
            Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = defect;
        }
    }
    return Cells;
}
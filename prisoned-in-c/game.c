#include <stdio.h> // to debug
#include <stdlib.h>
#include "game.h"
#include "strategy.h"
#include "formulas.h" // to debug
#include "sys/types.h"
#include "parameters.h"

Cell_ptr ** halfMatrixCreator(ParamPtr par){
    Cell_ptr **Cells = (Cell_ptr **) malloc(par->dim * par->dim * sizeof(Cell_str *));
    for(int i = 0; i<par->dim; i++){
            for(int j = 0; j<par->dim/2; j++ ){
                Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
                Cells[i][j]->memory = 0;
                Cells[i][j]->point = 0;
                Cells[i][j]->strategy = cooperate;
            }
            for(int j = par->dim/2; j<par->dim; j++ ){
                Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
                Cells[i][j]->memory = 0;
                Cells[i][j]->point = 0;
                Cells[i][j]->strategy = defect;
            }
        }
    return Cells;
    }

int neighborhoodApply(ParamPtr par, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr), Cell_ptr Cells[par->dim][par->dim] , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    
    for (int dir = 0; dir < 4; dir++) {
        int nrow = row + dx[dir];
        int ncol = col + dy[dir];

        if (nrow >= 0 && nrow < par->dim && ncol >= 0 && ncol < par->dim) {
            //if (fun == changeStrategy){ printf("try to change strat\n");} // to debug
            fun(Cells[row][col], Cells[nrow][ncol], par);
        }
    }
    return 0;
}

int oneRandNeighbourApply(ParamPtr par, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr), Cell_ptr Cells[par->dim][par->dim] , int row, int col){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    int nrow;
    int ncol;

    do{
        int dir = rand()%4;
        nrow = row + dx[dir];
        ncol = col + dy[dir];
    }while(!(nrow >= 0 && nrow < par->dim && ncol >= 0 && ncol < par->dim));

    fun(Cells[row][col], Cells[nrow][ncol], par);
    return 0;
}

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2, ParamPtr par){
    char move1 = player1->strategy();
    char move2 = player2->strategy();

    if ((move1 == 'C') && (move2 == 'C')) {
        return par->r;
    }
    else if ((move1 == 'C') && (move2 == 'D')) {
        return par->s;
    }
    else if ((move1 == 'D') && (move2 == 'C')) {
        return par->t;
    }
    else if ((move1 == 'D') && (move2 == 'D')) {
        return par->p;
    }
    else {
        return -1;
    }
}

// una funzione per trovare il colore della cella
u_int8_t * colorOfCell(Cell_ptr player){
    return strategyColor(player->strategy);
}
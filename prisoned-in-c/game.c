#include <stdio.h> // to debug
#include <stdlib.h>
#include "game.h"
#include "strategy.h"
#include "formulas.h" // to debug
#include "sys/types.h"
#include "parameters.h"

int allMatrixPointZero(ParamPtr param, Cell_ptr ** Cells){
    for(int i = 0; i<param->dim; i++){
        for(int j = 0; j<param->dim; j++){
            Cells[i][j]->point = 0;
        }
    }
    return 0;
}

int neighborhoodApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
                    Cell_ptr ** Cells){
    for(int i = 0; i<param->dim; i++ ){
        for(int j = 0; j<param->dim; j++){
            Cells[i][j]->point = 0;
            _oneNeighborhoodApply(param, fun, Cells, i, j);
        }
    }
    return 0;
}

int _oneNeighborhoodApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr),
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

int randNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr, float),
                    Cell_ptr ** Cells){
    u_int32_t intrand = xorshift32(rand());
    for(int i = 0; i<param->dim; i++){
        for(int j = 0; j<param->dim; j++){
            intrand = xorshift32(intrand);
            _oneRandNeighbourApply(param, fun, Cells, i, j, intrand);
        }
    }
    return 0;
}

int _oneRandNeighbourApply(ParamPtr param, int (*fun)(Cell_ptr, Cell_ptr, ParamPtr, float),
                    Cell_ptr ** Cells , int row, int col, u_int32_t intrand){
    int dx[] = { -1, 1, 0, 0 };  // line offset
    int dy[] = {  0, 0, -1, 1 }; // col offset
    int nrow;
    int ncol;

    do{
        int dir = intrand%4;
        nrow = row + dx[dir];
        ncol = col + dy[dir];
    }while(!(nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim));
    float floatrand = (float)intrand/4294967296.0f;
    fun(Cells[row][col], Cells[nrow][ncol], param, floatrand);
    return 0;
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

char (*_randomStrategy(void))(void){
    float num = rand();
    num = num/RAND_MAX;
    if(num<0.5){
        return cooperate;
    }
    else{
        return defect;
    }
}

Cell_ptr ** randMatrixCreator(ParamPtr param){
    Cell_ptr ** Cells =(Cell_ptr**) malloc(param->dim * sizeof(Cell_ptr));

    for(int i = 0; i<param->dim; i++){
        Cells[i] = (Cell_ptr*) malloc(param->dim * sizeof(Cell_ptr));
        for(int j = 0; j<param->dim; j++ ){
            Cells[i][j] = (Cell_str *) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = _randomStrategy();
        }
    }
    return Cells;
}
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

    int dir = intrand%4;
    nrow = row + dx[dir];
    ncol = col + dy[dir];
    if(nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim){
        /*
        printf("row: %i, col: %i, dx: %i, dy: %i\n", row, col, dx[dir], dy[dir]);
        printf("row: %i, col: %i, nrow: %i, ncol: %i\n", row, col, nrow, ncol);*/
        float floatrand = (float)intrand/4294967296.0f+0.5;
        fun(Cells[row][col], Cells[nrow][ncol], param, floatrand);
    }
    return 0;
}

int matrixSIRUpdate(int ** initial, int ** targhet, 
                SirParamPtr param){
    u_int32_t intrand = xorshift32(rand());
    for(int row = 0; row<param->dim; row++ ){
        for(int col = 0; col<param->dim; col++){
            intrand = xorshift32(intrand);
            cellSIRUpdate(row, col, initial, targhet, param, intrand);
        }
    }
    return 0;
}

/*
se sono a 0 e ho un vicino infetto, allora posso essere infettato con una certa probabilità
se sono infetto, allora divento resistente dopo un certo numero di iterazioni
se sono resistente, allora divento suscettibile dopo un certo numero di iterazioni
*/

int cellSIRUpdate(int row, int col, int ** initial, int ** targhet, 
                SirParamPtr param, int intrand){
    
    targhet[row][col] = initial[row][col];
    if(initial[row][col] == 0){
        int dx[] = { -1, 1, 0, 0 };  // line offset
        int dy[] = {  0, 0, -1, 1 }; // col offset
        for (int dir = 0; dir < 4; dir++) { //von newman neighboors
            int nrow = row + dx[dir];
            int ncol = col + dy[dir];
            intrand = xorshift32(intrand);

            if (nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim){ // valid position
                if(initial[nrow][ncol]>0 && initial[nrow][ncol]<=param->infected_time){ // near infected
                    float floatrand = (float)intrand/4294967296.0f + 0.5;
                    if(floatrand <= param->propagation_ratio){ //infection
                        targhet[row][col] = 1;
                    }
                }
            }
        }
        return 0;
    }
    if (initial[row][col] == param->resistent_time){
        if(param->reinfected !=0){
            targhet[row][col] = 0;
            return 0;
        }
        return 0;
    }
    targhet[row][col] = initial[row][col] + 1;
    return 0;
}

int matrixFireUpdate(int ** initial, int ** targhet, 
                FireParamPtr param){
    u_int32_t intrand = xorshift32(rand());
    for(int row = 0; row<param->dim; row++ ){
        for(int col = 0; col<param->dim; col++){
            intrand = xorshift32(intrand);
            cellFireUpdate(row, col, initial, targhet, param, intrand);
        }
    }
    return 0;
}

int cellFireUpdate(int row, int col, int ** initial, int ** targhet, 
                FireParamPtr param, int intrand){
    targhet[row][col] = initial[row][col];
    if (initial[row][col] == 1){ // tree
        int dir[] = {0, -1, 1};
        for (int pos = 1; pos <9; pos++){
            int nrow = row + dir[pos%3];
            int ncol = col + dir[pos/3];
            intrand = xorshift32(intrand);
            if (nrow >= 0 && nrow < param->dim && ncol >= 0 && ncol < param->dim){ // valid position
                if(initial[nrow][ncol]==1){ // near infected
                    float floatrand = (float)intrand/4294967296.0f + 0.5;
                    if(floatrand <= param->propagation_ratio){
                        targhet[row][col] = 2;
                    }
                }
            }
        }
        return 0;
    }
    if (initial[row][col] == 2){ // on fire
        targhet[row][col] = 3;
        return 0;
    }
    return 0;

    
}

// una funzione per trovare il colore della cella
u_int8_t * colorOfCell(Cell_ptr player){
    return strategyColor(player->strategy);
}

Cell_ptr ** halfMatrixCreator(ParamPtr param){
    Cell_ptr ** Cells =(Cell_ptr**) malloc(param->dim * sizeof(Cell_ptr*));

    for(int i = 0; i<param->dim; i++){
        Cells[i] = (Cell_ptr*) malloc(param->dim * sizeof(Cell_ptr));
        for(int j = 0; j<param->dim/2; j++ ){
            Cells[i][j] = (Cell_str *) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = get_cooperate();
        }
        for(int j = param->dim/2; j<param->dim; j++ ){
            Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = get_defect();
        }
    }
    return Cells;
}

Cell_ptr ** randMatrixCreator(ParamPtr param){
    Cell_ptr ** Cells =(Cell_ptr**) malloc(param->dim * sizeof(Cell_ptr*));

    for(int i = 0; i<param->dim; i++){
        Cells[i] = (Cell_ptr*) malloc(param->dim * sizeof(Cell_ptr));
        for(int j = 0; j<param->dim; j++ ){
            Cells[i][j] = (Cell_str *) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = randomStrategy();
        }
    }
    return Cells;
}

int ** intMatrixCreator(ParamPtr param){
    int ** matrix =(int**) malloc(param->dim * sizeof(int*));
    for(int i = 0; i<param->dim; i++){
        matrix[i] = (int*) malloc(param->dim * sizeof(int));
        for(int j = 0; j<param->dim; j++ ){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

int ** intMatrixPopulator(SirParamPtr param, int ** matrix){
    for(int i = 0; i<param->dim; i++){
        for(int j = 0; j<param->dim; j++ ){
            double randnum = (double)rand()/RAND_MAX;
            if(randnum < param->initial_infected_ratio){
                matrix[i][j] = 1;
            }
        }
    }
    return matrix;
}

int ** FireMatrixCreator(FireParamPtr param){
    int ** matrix =(int**) malloc(param->dim * sizeof(int*));
    u_int32_t intrand = xorshift32(rand());
    printf("tree: %f, burn: %f\n", param->initial_tree_ratio, param->initial_burn_ratio);
    for(int i = 0; i<param->dim; i++){
        matrix[i] = (int*) malloc(param->dim * sizeof(int));
        for(int j = 0; j<param->dim; j++ ){
            intrand = xorshift32(intrand);
            float floatrand = ((float)intrand)/(4294967296.0f);
            matrix[i][j] = 0;
            printf("%f\n", floatrand);
            if (floatrand<param->initial_tree_ratio){
                matrix[i][j] = 1;
            }
            if (floatrand<param->initial_burn_ratio){
                matrix[i][j] = 2;
            }
        }
    }
    return matrix;
}
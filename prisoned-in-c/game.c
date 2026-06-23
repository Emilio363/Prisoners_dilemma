#include <stdio.h> // to debug
#include <stdlib.h>
#include <math.h>
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
        float floatrand = (float)intrand/4294967296.0f;
        fun(Cells[row][col], Cells[nrow][ncol], param, floatrand);
    }
    return 0;
}

int matrixSIRUpdate(int ** initial, int ** target, 
                SirParamPtr param){
    u_int32_t intrand = xorshift32(rand());
    for(int row = 0; row<param->dim; row++ ){
        for(int col = 0; col<param->dim; col++){
            intrand = xorshift32(intrand);
            cellSIRUpdate(row, col, initial, target, param, intrand);
        }
    }
    return 0;
}

int cellSIRUpdate(int row, int col, int ** initial, int ** target, 
                SirParamPtr param, u_int32_t intrand){
    
    target[row][col] = initial[row][col];
    if(initial[row][col] == 0){
        int dx[] = { -1, 1, 0, 0 };  // line offset
        int dy[] = {  0, 0, -1, 1 }; // col offset
        for (int dir = 0; dir < 4; dir++) { //von newman neighboors
            int nrow = (row + dx[dir] + param->dim)%param->dim;
            int ncol = (col + dy[dir] + param->dim)%param->dim;
            intrand = xorshift32(intrand);
            if(initial[nrow][ncol]>0 && initial[nrow][ncol]<=param->infected_time){ // near infected
                float floatrand = (float)intrand/4294967296.0f;
                if(floatrand <= param->propagation_ratio){ //infection
                    target[row][col] = 1;
                }
            }
        }
        return 0;
    }
    if (initial[row][col] == param->resistent_time){
        if(param->reinfected !=0){
            target[row][col] = 0;
            return 0;
        }
        return 0;
    }
    target[row][col] = initial[row][col] + 1;
    return 0;
}

int matrixFireUpdate(int ** initial, int ** target, 
                FireParamPtr param){
    u_int32_t intrand = xorshift32(rand());
    for(int row = 0; row<param->dim; row++ ){
        for(int col = 0; col<param->dim; col++){
            intrand = xorshift32(intrand);
            cellFireUpdate(row, col, initial, target, param, intrand);
        }
    }
    return 0;
}

int cellFireUpdate(int row, int col, int ** initial, int ** target, 
                FireParamPtr param, u_int32_t intrand){
    target[row][col] = initial[row][col];
    if (initial[row][col] == 1){ // tree
        int dir[] = {-1, 0, 1};
        for (int i = 0; i <3; i++){ // moore neighboors
            for (int j = 0; j<3; j++){
                int nrow = (row + dir[j] + param->dim)%param->dim;
                int ncol = (col + dir[2-i] + param->dim)%param->dim;
                intrand = xorshift32(intrand);
                if(initial[nrow][ncol]==2){ // near infected
                    float floatrand = (float)intrand/4294967296.0f;
                    if(floatrand <= param->propagation_matrix[i][j]){
                        target[row][col] = 2;
                        // printf("%i %f\n", i, floatrand);
                    }
                    else {
                        // printf("x: %i, y: %i, cos: %f\n", i, j, param->propagation_matrix[i][j]);
                    }
                }
            }
        }
        return 0;
    }
    if (initial[row][col] == 2){ // on fire
        target[row][col] = 3;
        return 0;
    }
    return 0;
}

int matrixIsingUpdate(int ** initial, int ** target, 
                IsingParamPtr param){
    
    u_int32_t intrand = xorshift32(rand());
    for (int i = 0; i< param->step_iteration; i++){
        int row = intrand%param->dim;
        int col = intrand/param->dim%param->dim;
        cellIsingUpdate(row, col, initial, target, param, intrand);
    }
    return 0;
}

int cellIsingUpdate(int row, int col, int ** initial, int ** target, 
                IsingParamPtr param, u_int32_t intrand){
    int s = initial[row][col];
    int neighbour_sum = 0;
    if (param->periodic_boundary){ //periodic boundary
        neighbour_sum =
            initial[(row - 1 + param->dim) % param->dim][col]
            + initial[(row + 1) % param->dim][col]
            + initial[row][(col - 1 + param->dim) % param->dim]
            + initial[row][(col + 1) % param->dim];
    }
    else{ // static boundary
        if(row > 0) neighbour_sum += initial[row - 1][col];
        if(row < param->dim - 1) neighbour_sum += initial[row + 1][col];
        if(col > 0) neighbour_sum += initial[row][col - 1];
        if(col < param->dim - 1)neighbour_sum += initial[row][col + 1];
    }
    double deltaE = - 2 * s * (param->coupling * neighbour_sum + param->magnetic_field);
    
    int accept = 0;

    if(deltaE <= 0.0) {
        accept = 1;
    }
    else {
        float rnd = (float)intrand / 4294967296.0f;
        double p = exp(-deltaE / param->temperature);
        if(rnd < p)
            accept = 1;
    }
    if(accept)
    {
        target[row][col] = -s;
        initial[row][col] = -s;
        param->hamiltonian += deltaE;
        return 1;
    }
    target[row][col] = s;
    initial[row][col] = s;
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
    for(int i = 0; i<param->dim; i++){
        matrix[i] = (int*) malloc(param->dim * sizeof(int));
        for(int j = 0; j<param->dim; j++ ){
            intrand = xorshift32(intrand);
            float floatrand = (float)intrand/4294967296.0f;
            matrix[i][j] = 0;
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

int ** isingMatrix(IsingParamPtr param){
    int ** matrix =(int**) malloc(param->dim * sizeof(int*));
    u_int32_t intrand = xorshift32(rand());
    for(int i = 0; i<param->dim; i++){
        matrix[i] = (int*) malloc(param->dim * sizeof(int));
        for(int j = 0; j<param->dim; j++ ){
            intrand = xorshift32(intrand);
            float floatrand = (float)intrand/4294967296.0f;
            matrix[i][j] = (floatrand < param->initial_ratio) ? 1 : -1;
        }
    }
    double H = 0.0;
    if (param->periodic_boundary){ // with periodic boundary
        for(int i = 0; i < param->dim; i++)
        {
            for(int j = 0; j < param->dim; j++)
            {
                int s = matrix[i][j];
                int right = matrix[i][(j + 1) % param->dim];
                int down  = matrix[(i + 1) % param->dim][j];
                H -= param->coupling * s * right;
                H -= param->coupling * s * down;
                H -= param->magnetic_field * s;
            }
        }
    }
    else{ // with static boundary
        for(int i = 0; i < param->dim; i++){ 
            for(int j = 0; j < param->dim; j++){
                int s = matrix[i][j];
                if(j + 1 < param->dim){
                    H -= param->coupling * s * matrix[i][j + 1];
                }
                if(i + 1 < param->dim){
                    H -= param->coupling * s * matrix[i + 1][j];
                }
                H -= param->magnetic_field * s;
            }
        }
    }
    param->hamiltonian = H;
    return matrix;
}

int ** copyMatrix(int ** initial, int dim){
    int ** matrix =(int**) malloc(dim * sizeof(int*));
    for(int i = 0; i<dim; i++){
        matrix[i] = (int*) malloc(dim * sizeof(int));
        for(int j = 0; j<dim; j++ ){
            matrix[i][j] = initial[i][j];
        }
    }
    return matrix;
}
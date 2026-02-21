#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "game.h"
#include "formulas.h"
#include "ppm.h"
#include <math.h>
#include "parameters.h"

void stampStrategies(ParamPtr par, Cell_ptr mat[par->dim][par->dim]) {
    printf("\n strategies: \n");
    for (int i = 0; i < par->dim; i++) {
        for (int j = 0; j < par->dim; j++) {
            printf("%c ", (mat[i][j]->strategy == cooperate) ? 'C' : 'D');
        }
        printf("\n");
    }
    printf("\n");
}

void stamPoints(ParamPtr par, Cell_ptr mat[par->dim][par->dim]) {
    printf("\n points: \n");
    for (int i = 0; i < par->dim; i++) {
        for (int j = 0; j < par->dim; j++) {
            printf("%f ", mat[i][j]->point);
        }
        printf("\n");
    }
    printf("\n");
}

void stamMemory(ParamPtr par, Cell_ptr mat[par->dim][par->dim]) {
    printf("\n memories \n");
    for (int i = 0; i < par->dim; i++) {
        for (int j = 0; j < par->dim; j++) {
            printf("%i ", mat[i][j]->memory);
        }
        printf("\n");
    }
    printf("\n");
}

int printMatrix(ParamPtr par, Cell_ptr matrix[par->dim][par->dim], char * image_path){

    ppm_str destination_image;
    int height = par->dim*par->image_proportion;
    int width = par->dim*par->image_proportion;

    int err3 = createPPM(image_path, height, width, &destination_image);
    if (err3 != 0){
        printf("Errore nella creazione dell'immagine");
        return -6;
    }
    printf("Dimensione del file= %d\n", (&destination_image)->size);
    int chec = CellsMatrixinPPM(par->dim, matrix, &destination_image);
    if (chec != 1){
        printf("grande tragedia");
        return -100;
    }
    return 1;
}

char (*randomStrategy(void))(void){
    float num = rand();
    num = num/RAND_MAX;
    if(num<0.5){
        return cooperate;
    }
    else{
        return defect;
    }
}

int main(){
    ParamPtr par = standardParameters();
    Cell_ptr **Cells = halfMatrixCreator(par);
    printf("work1\n");
    stampStrategies(par, Cells);
    
    for(int k = 0; k < par->iteration; k++){ // number of epoc
        for(int i = 0; i<par->dim; i++ ){
            for(int j = 0; j<par->dim; j++){
                Cells[i][j]->point = 0;
                neighborhoodApply(par, incrementPoint, Cells, i, j);
            }
        }

        for(int i = 0; i<par->dim; i++){
            for(int j = 0; j<par->dim; j++){
                oneRandNeighbourApply(par, changeStrategy, Cells, i, j);
            }
        }
//        double logarithm = log2((double)k); // (int)logarithm ==logarithm
        if ( k%par->image_step == 0){
            char filename[25];
            printf("stampa");
            sprintf(filename, "%d-image.ppm", k);
            printMatrix(par, Cells, filename);
        }
    }

    return 0;
}
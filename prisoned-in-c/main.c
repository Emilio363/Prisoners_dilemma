#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "game.h"
#include "formulas.h"
#include "ppm.h"
#include <math.h>
#include "parameters.h"

void stampStrategies(ParamPtr param, Cell_ptr mat[param->dim][param->dim]) {
    printf("\n strategies: \n");
    for (int i = 0; i < param->dim; i++) {
        for (int j = 0; j < param->dim; j++) {
            printf("%c ", (mat[i][j]->strategy == cooperate) ? 'C' : 'D');
        }
        printf("\n");
    }
    printf("\n");
}

void stamPoints(ParamPtr param, Cell_ptr mat[param->dim][param->dim]) {
    printf("\n points: \n");
    for (int i = 0; i < param->dim; i++) {
        for (int j = 0; j < param->dim; j++) {
            printf("%f ", mat[i][j]->point);
        }
        printf("\n");
    }
    printf("\n");
}

void stamMemory(ParamPtr param, Cell_ptr mat[param->dim][param->dim]) {
    printf("\n memories \n");
    for (int i = 0; i < param->dim; i++) {
        for (int j = 0; j < param->dim; j++) {
            printf("%i ", mat[i][j]->memory);
        }
        printf("\n");
    }
    printf("\n");
}

int printMatrix(ParamPtr param, Cell_ptr ** mat, char * image_path){

    ppm_str destination_image;
    int height = param->dim*param->image_proportion;
    int width = param->dim*param->image_proportion;

    int err3 = createPPM(image_path, height, width, &destination_image);
    if (err3 != 0){
        printf("Errore nella creazione dell'immagine");
        return -6;
    }
    printf("Dimensione del file= %d\n", (&destination_image)->size);
    int chec = CellsMatrixinPPM(param->dim, mat, &destination_image);
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
    ParamPtr param = standardParameters();

    printf("init \n");
    Cell_ptr ** Cells = halfMatrixCreator(param);

    for(int k = 0; k < param->iteration; k++){ // number of epoc
        for(int i = 0; i<param->dim; i++ ){
            for(int j = 0; j<param->dim; j++){
                Cells[i][j]->point = 0;
                neighborhoodApply(param, incrementPoint, Cells, i, j);
            }
        }

        for(int i = 0; i<param->dim; i++){
            for(int j = 0; j<param->dim; j++){
                oneRandNeighbourApply(param, changeStrategy, Cells, i, j);
            }
        }
//        double logarithm = log2((double)k); // (int)logarithm ==logarithm

        if ( k%param->image_step == 0){
            char filename[25];
            sprintf(filename, "%d-image.ppm", k);
            printMatrix(param, Cells, filename);
        }
    }

    return 0;
}
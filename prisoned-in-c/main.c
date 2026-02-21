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

void NewPrintMatrix(ParamPtr param, Cell_ptr ** Cells, int k){
            char filename[25];
            sprintf(filename, "%d-image.ppm", k);
            printMatrix(param, Cells, filename);
}

float evalCoopPercent(ParamPtr param, Cell_ptr ** Cells){
    float coop_percent = 0;
    for(int i = 0; i<param->dim; i++){
        for(int j = 0; j<param->dim; j++ ){
            //pritnf(Cells[i][j]->strategy == cooperate);
            if(Cells[i][j]->strategy == cooperate){
                coop_percent++;
            }
        }
    }
    return coop_percent/(param->dim*param->dim);

}

int main(){
    ParamPtr param = standardParameters();
    Cell_ptr ** Cells = randMatrixCreator(param);

    for(int k = 0; k < param->iteration; k++){ // number of epoc
        neighborhoodApply(param, incrementPoint, Cells);
        randNeighbourApply(param, changeStrategy, Cells);
        if ( k%param->image_step == 0){
            printf("iteration %d, coop percent: %f\n", k, evalCoopPercent(param, Cells));
            NewPrintMatrix(param, Cells, k);
        }
    }
    return 0;
}
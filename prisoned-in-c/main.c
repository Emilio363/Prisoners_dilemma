#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "strategy.h"
#include "game.h"
#include "formulas.h"
#include "ppm.h"
#include "parameters.h"
#include "tests.h"



void stampStrategies(ParamPtr param, Cell_ptr ** mat){
    printf("\n strategies: \n");
    for (int i = 0; i < param->dim; i++) {
        for (int j = 0; j < param->dim; j++) {
            printf("%c ", (mat[i][j]->strategy == cooperate) ? 'C' : 'D');
        }
        printf("\n");
    }
    printf("\n");
}

void stamPoints(ParamPtr param, Cell_ptr ** mat){
    printf("\n points: \n");
    for (int i = 0; i < param->dim; i++) {
        for (int j = 0; j < param->dim; j++) {
            printf("%f ", mat[i][j]->point);
        }
        printf("\n");
    }
    printf("\n");
}

void stampMemory(ParamPtr param, Cell_ptr ** mat){
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

void NewPrintMatrix(ParamPtr param, Cell_ptr ** Cells, int iteration){
            char filename[25];
            sprintf(filename, "%d-image.ppm", iteration);
            printMatrix(param, Cells, filename);
}

float evalCoopPercent(ParamPtr param, Cell_ptr ** Cells){
    float coop_percent = 0;
    for(int i = 0; i<param->dim; i++){
        for(int j = 0; j<param->dim; j++ ){
            if(Cells[i][j]->strategy == cooperate){
                coop_percent++;
            }
        }
    }
    return coop_percent/(param->dim*param->dim);

}

void freeMatrix(Cell_ptr **Cells, int dim){
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            free(Cells[i][j]);
        }
        free(Cells[i]);
    }
    free(Cells);
}

int main(){
    
    ParamPtr (* parameters)() = funkyParameters;
    Cell_ptr ** matri = halfMatrixCreator(parameters());
    printf("%f\n", evalCoopPercent(parameters(), matri));
    float startTime = (float)clock()/3000000;
    percentSampling1(parameters);
//    percentSampling2(parameters);
//    betaVariation(parameters);
    float endTime = (float)clock()/3000000;

    float timeElapsed1 = endTime - startTime;
    
    printf("first: %f seconds\n", timeElapsed1);
}
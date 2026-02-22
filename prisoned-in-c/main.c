#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "game.h"
#include "formulas.h"
#include "ppm.h"
#include <math.h>
#include "parameters.h"
#include <omp.h>



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

void freeMatrix(Cell_ptr **Cells, int dim) {
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            free(Cells[i][j]);
        }
        free(Cells[i]);
    }
    free(Cells);
}

int memoryTemptationPercent_test(){
    int memories[] = {0,1,3,5,7,9};
    double t_arr[20];
    for(int i = 0; i<20; i++){
        t_arr[i] = 1.0 + i*0.025;
    }

    FILE *fp = fopen("output.csv", "w");
     //collapse(2) num_threads(6)
    #pragma omp parallel for
    for (int m = 0; m < 6; m++) {
        for (int t_i = 0; t_i < 20; t_i++) {

            ParamPtr param = standardParameters();
            param->max_memory = memories[m];
            param->t = t_arr[t_i];
            printf("thread %i, memory: %i, Temptation: %f\n", omp_get_thread_num(), param->max_memory, param->t);


            Cell_ptr ** Cells = randMatrixCreator(param);
            for(int k = 0; k < param->iteration; k++){ // number of epoc
                neighborhoodApply(param, incrementPoint, Cells);
                randNeighbourApply(param, changeStrategy, Cells);
            }
            //NewPrintMatrix(param, Cells, param->iteration+m*100+t_i*10);
            printf("percent: %f, memory: %i, Temptation: %f\n", evalCoopPercent(param, Cells), param->max_memory, param->t);
            //#pragma omp critical
            {
                fprintf(fp, "%f, %f, %i\n", param->t, evalCoopPercent(param, Cells), param->max_memory);
            }
            freeMatrix(Cells, param->dim);
        }
    }

    fclose(fp);
    return 0;
}

int memoryRationality(){
        int memories[10];
    double k_arr[3]={0.1, 0.2, 0.3};
    for(int i = 0; i<10; i++){
        memories[i] = 10*i;
    }

    FILE *fp = fopen("output.csv", "w");

    for (int m = 0; m < 10; m++) {
        for (int t_i = 0; t_i < 3; t_i++) {

            ParamPtr param = standardParameters();
            param->max_memory = memories[m];
            param->k = k_arr[t_i];

            Cell_ptr ** Cells = randMatrixCreator(param);
            for(int k = 0; k < param->iteration; k++){ // number of epoc
                neighborhoodApply(param, incrementPoint, Cells);
                randNeighbourApply(param, changeStrategy, Cells);
            }
            //NewPrintMatrix(param, Cells, param->iteration+m*100+t_i*10);
            printf("%f\n", evalCoopPercent(param, Cells));
            fprintf(fp, "%i, %f, %f\n", param->max_memory, evalCoopPercent(param, Cells), param->k);
            freeMatrix(Cells, param->dim);
        }
    }

    fclose(fp);
    return 0;
}

int main(){
    memoryTemptationPercent_test();

}
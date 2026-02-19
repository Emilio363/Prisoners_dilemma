#include <stdio.h>
#include <stdlib.h>
#include "strategy.h"
#include "game.h"
#include "formulas.h"
#include "ppm.h"
#include <math.h>
#include "parameters.h"

void stampStrategies(int righe, int colonne, Cell_ptr mat[righe][colonne]) {
    printf("\n strategies: \n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%c ", (mat[i][j]->strategy == cooperate) ? 'C' : 'D');
        }
        printf("\n");
    }
    printf("\n");
}

void stamPoints(int righe, int colonne, Cell_ptr mat[righe][colonne]) {
    printf("\n points: \n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%f ", mat[i][j]->point);
        }
        printf("\n");
    }
    printf("\n");
}

void stamMemory(int righe, int colonne, Cell_ptr mat[righe][colonne]) {
    printf("\n memories \n");
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%i ", mat[i][j]->memory);
        }
        printf("\n");
    }
    printf("\n");
}

int printMatrix(Cell_ptr matrix[DIM][DIM], char * image_path, int rateo){

    ppm_str destination_image;
    int height = DIM*rateo;
    int width = DIM*rateo;

    int err3 = createPPM(image_path, height, width, &destination_image);
    if (err3 != 0){
        printf("Errore nella creazione dell'immagine");
        return -6;
    }
    printf("Dimensione del file= %d\n", (&destination_image)->size);
    int chec = CellsMatrixinPPM(DIM, matrix, &destination_image);
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
    //aggiungi la possibilità di inserire dati particolare tipo:
    // dimensione della matrice, dim dell'imagine ...
    Cell_ptr Cells[DIM][DIM];
    
    // matrix creation PARALLELIZE
    for(int i = 0; i<DIM; i++){
        for(int j = 0; j<DIM/2; j++ ){
            Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = cooperate;
        }
        for(int j = DIM/2; j<DIM; j++ ){
            Cells[i][j] = (Cell_ptr) malloc(sizeof(Cell_str));
            Cells[i][j]->memory = 0;
            Cells[i][j]->point = 0;
            Cells[i][j]->strategy = defect;
        }
    }

    for(int k = 0; k < ITERATION; k++){ // number of epoc
        for(int i = 0; i<DIM; i++ ){
            for(int j = 0; j<DIM; j++){
                Cells[i][j]->point = 0;
                neighborhoodApply(incrementPoint, DIM, Cells, i, j);
            }
        }

        for(int i = 0; i<DIM; i++){
            for(int j = 0; j<DIM; j++){
                oneRandNeighbourApply(changeStrategy, DIM, Cells, i, j);
            }
        }
//        double logarithm = log2((double)k); // (int)logarithm ==logarithm
        if ( k%IMAGE_STEP == 0){
            char filename[20];
            printf("stampa");
            sprintf(filename, "%d-image.ppm", k);
            printMatrix(Cells, filename, IMAGE_PROPORTION);
        }


    }

    return 0;
}
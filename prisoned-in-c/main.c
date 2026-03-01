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
#include "miscellaneous.h"

int temptatioUnparallel(ParamPtr (*parFun)()){
    int memories[] = {0,1,3,5,7,9};
    double t_arr[20];
    for(int i = 0; i<20; i++){
        t_arr[i] = 1.0 + i*0.025;
    }

    FILE *fp = fopen("output_temptation.csv", "w");
    for (int m = 0; m < 6; m++) {
        for (int t_i = 0; t_i < 20; t_i++) {

            ParamPtr param = parFun();
            param->max_memory = memories[m];
            param->t = t_arr[t_i];
            printf("thread %i, memory: %i, Temptation: %f\n", omp_get_thread_num(), param->max_memory, param->t);

            Cell_ptr ** Cells = randMatrixCreator(param);
            for(int k = 0; k < param->max_iteration; k++){ // number of epoc
                neighborhoodApply(param, incrementPoint, Cells);
                randNeighbourApply(param, changeStrategy, Cells);
            }
            printf("percent: %f, memory: %i, Temptation: %f\n", evalCoopPercent(param, Cells), param->max_memory, param->t);
            
            fprintf(fp, "%f, %f, %i\n", param->t, evalCoopPercent(param, Cells), param->max_memory);
            freeMatrix(Cells, param->dim);
        }
    }

    fclose(fp);
    return 0;
}

int temptatioParallel(ParamPtr (*parFun)()){
    int memories[6] = {0,1,3,5,7,9};
    double t_arr[20];
    for(int i = 0; i<20; i++){
        t_arr[i] = 1.0 + i*0.025;
    }

    FILE *fp = fopen("output_temptation_par.csv", "w");
    #pragma omp parallel for collapse(2)
    for (int m = 0; m < 6; m++) {
        for (int t_i = 0; t_i < 20; t_i++) {

            ParamPtr param = parFun();
            param->max_memory = memories[m];
            param->t = t_arr[t_i];
            printf("thread %i, memory: %i, Temptation: %f\n", omp_get_thread_num(), param->max_memory, param->t);


            Cell_ptr ** Cells = randMatrixCreator(param);
            for(int k = 0; k < param->max_iteration; k++){ // number of epoc
                neighborhoodApply(param, incrementPoint, Cells);
                randNeighbourApply(param, changeStrategy, Cells);
            }
            printf("percent: %f, memory: %i, Temptation: %f\n", evalCoopPercent(param, Cells), param->max_memory, param->t);
            #pragma omp critical
            {
                fprintf(fp, "%f, %f, %i\n", param->t, evalCoopPercent(param, Cells), param->max_memory);
            }
            freeMatrix(Cells, param->dim);
        }
    }

    fclose(fp);
    return 0;
}

int memoryRationality(ParamPtr (*parFun)()){
    int memories[10];
    double k_arr[3]={0.1, 0.2, 0.3};
    for(int i = 0; i<10; i++){
        memories[i] = 10*i;
    }

    FILE *fp = fopen("output_rationality.csv", "w");

    for (int m = 0; m < 10; m++) {
        for (int t_i = 0; t_i < 3; t_i++) {

            ParamPtr param = parFun();
            param->max_memory = memories[m];
            param->k = k_arr[t_i];

            Cell_ptr ** Cells = randMatrixCreator(param);
            for(int k = 0; k < param->max_iteration; k++){ // number of epoc
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

int debuggingMode(ParamPtr (*parFun)()){
    ParamPtr param = parFun();

    Cell_ptr ** Cells = randMatrixCreator(param);
    for(int k = 0; k < 10; k++){ // number of epoc
        neighborhoodApply(param, incrementPoint, Cells);
        randNeighbourApply(param, changeStrategy, Cells);
            printf("percernt: %f\n", evalCoopPercent(param, Cells));

            stampStrategies(param, Cells);
            printf("percernt: %f\n", evalCoopPercent(param, Cells));
            stampMemory(param, Cells);

            printf("percernt: %f\n", evalCoopPercent(param, Cells));
    }
    //NewPrintMatrix(param, Cells, param->iteration+m*100+t_i*10);
    printf("final evaluation: %f\n", evalCoopPercent(param, Cells));
    freeMatrix(Cells, param->dim);

    return 0;
}

int percentSampling1(ParamPtr (*parFun)()){
    int memories[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    FILE *fp = fopen("output_percentSampling1.csv", "w");

    for (int m = 0; m < 11; m++){
        ParamPtr param = parFun();
        param->max_memory = memories[m];
        Cell_ptr ** Cells = randMatrixCreator(param);
        fprintf(fp, "%i, %f, %i\n", 0, evalCoopPercent(param, Cells), param->max_memory);
        for(int k = 1; k < param->max_iteration; k++){ // number of epoc
            neighborhoodApply(param, incrementPoint, Cells);
            randNeighbourApply(param, changeStrategy, Cells);
            allMatrixPointZero(param, Cells);
            fprintf(fp, "%i, %f, %i\n", k, evalCoopPercent(param, Cells), param->max_memory);
            
        }
        freeMatrix(Cells, param->dim);
    }
    fclose(fp);
    return 0;
}

int percentSampling2(ParamPtr (*parFun)()){
    int memories[6] = {20, 30, 50, 80, 100, 200};

    FILE *fp = fopen("output_percentSampling2.csv", "w");

    for (int m = 0; m < 6; m++){
        ParamPtr param = parFun();
        param->max_memory = memories[m];
        Cell_ptr ** Cells = randMatrixCreator(param);
        printf("%i, %f, %i\n", 0, evalCoopPercent(param, Cells), param->max_memory);
        for(int k = 1; k < param->max_iteration; k++){ // number of epoc
            neighborhoodApply(param, incrementPoint, Cells);
            randNeighbourApply(param, changeStrategy, Cells);   
            fprintf(fp, "%i, %f, %i\n", k, evalCoopPercent(param, Cells), param->max_memory);
            
        }
        freeMatrix(Cells, param->dim);
    }
    fclose(fp);
    return 0;
}

int betaVariation(ParamPtr (*parFun)()){
    int betas[5] = {0.1, 0.3, 0.5, 0.7, 0.9};

    FILE *fp = fopen("output_beta.csv", "w");

    for (int b = 0; b < 5; b++){
        ParamPtr param = parFun();
        param->max_memory = 7;
        param->t = 1.05;
        param->beta = betas[b];
        Cell_ptr ** Cells = randMatrixCreator(param);
        for(int k = 0; k < param->max_iteration; k++){ // number of epoc
            param->actual_iteration = k;
            neighborhoodApply(param, incrementPoint, Cells);
            randNeighbourApply(param, changeStrategy, Cells);
            fprintf(fp, "%i, %f, %f\n", k, evalCoopPercent(param, Cells), param->beta);
            
        }
        freeMatrix(Cells, param->dim);
    }
    fclose(fp);
    return 0;
}

int myTemptationBetaMem(ParamPtr (*parFun)()){
    int memories[3] = {0,1,9};
    float betas[6] = {0.1,0.2,0.3,0.5,0.7,0.9};
    int t_dim = 16;
    double t_arr[t_dim];

    for(int i = 0; i<t_dim; i++){
        t_arr[i] = 1.0 + i*0.01;
    }

    for(int m = 0; m<3; m++){
        char filename[100];
        printf("memory: %i\n", memories[m]);
        snprintf(filename, sizeof(filename), "temp_beta_mem_%d.csv", memories[m]);

        FILE *fp = fopen(filename, "w");
        #pragma omp parallel for collapse(2)
        for (int b = 0; b < 6; b++) {
            for (int t_i = 0; t_i < t_dim; t_i++) {

                ParamPtr param = parFun();
                param->max_memory = memories[m];
                param->beta = betas[b];
                param->t = t_arr[t_i];
                printf("start N ciclo %i\n", m*t_dim+t_i);


                Cell_ptr ** Cells = randMatrixCreator(param);
                for(int k = 0; k < param->max_iteration; k++){ // number of epoc
                    neighborhoodApply(param, incrementPoint, Cells);
                    randNeighbourApply(param, changeStrategy, Cells);
                }
                printf("END N ciclo %i\n", m*20+t_i);
                #pragma omp critical
                {
                    fprintf(fp, "%f, %f, %i\n", param->t, evalCoopPercent(param, Cells), param->beta);
                }
                freeMatrix(Cells, param->dim);
            }
        }

        fclose(fp);
    }
    return 0;
}

int myPercentKBetaMulti(ParamPtr (*parFun)()){
    float betas[6] = {0.1, 0.2, 0.3, 0.5, 0.7, 0.9};
    float ks[3] = {0.1, 0.5, 1.0};
    for (int k = 0; k < 3; k++){
        char filename[100];
        printf("memory: %f\n", betas[k]);
        snprintf(filename, sizeof(filename), "beta_multi_%f.csv", betas[k]);

        FILE *fp = fopen(filename, "w");
        for(int multi = 1; multi < 10; multi++){
            for (int m = 0; m < 6; m++){
                ParamPtr param = parFun();
                param->beta = betas[m];
                Cell_ptr ** Cells = randMatrixCreator(param);
                for(int k = 1; k < param->max_iteration; k++){ // number of epoc
                    neighborhoodApply(param, incrementPoint, Cells);
                    randNeighbourApply(param, changeStrategy, Cells);
                    allMatrixPointZero(param, Cells);
                    fprintf(fp, "%i, %f, %f, %i\n", k, evalCoopPercent(param, Cells), param->beta, multi);
                    
                }
                freeMatrix(Cells, param->dim);
            }
        }
        fclose(fp);
    }
    return 0;
}


int main(){

    ParamPtr (* parameters)() = easyParameters;

    float startTime = (float)clock()/3000000;
    myPercentKBetaMulti(parameters);
    float endTime = (float)clock()/3000000;

    float timeElapsed1 = endTime - startTime;
    
    printf("first: %f seconds\n", timeElapsed1);
}
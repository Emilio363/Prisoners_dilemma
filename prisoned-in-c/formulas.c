#include <math.h>
#include <stdlib.h>
#include "game.h"
#include <stdio.h>
#include "parameters.h"


float fermi(float point1, float point2, ParamPtr param) {    
    float prob = 1 / (1 + exp((point1 - point2) / param->k));
    return prob;
}

float H_x(int memory, ParamPtr param) {
    if (param->max_memory == 0){
        return 1;
    }else{
        return 1-(1-param->beta)*memory/param->max_memory;}
}

int incrementPoint(Cell_ptr player1, Cell_ptr player2, ParamPtr param){
    player1->point += oneGame_oneResult(player1, player2, param);
    return 0;
}

int changeStrategy(Cell_ptr player1, Cell_ptr player2, ParamPtr param){
    float thisrand = rand();
//    printf("maybe change");  //to debug
    
    float prob = H_x(player1->memory, param)*fermi(player1->point, player2->point, param);
    char (*newstrategy)() = player1->strategy;
    
    thisrand /= RAND_MAX; // to have a number between 0 and 1
//    printf(" %f, %f, %i \n", prob, thisrand, myrand); //to debug
    if (prob < thisrand){
//        printf("changing strategy\n"); //to debug
        newstrategy = player2->strategy;
    }
    if (newstrategy == player1->strategy){
        if (player1->memory<param->max_memory){
            player1->memory++;
        }
    }
    else{
        player1->memory = 0;
        player1->strategy = newstrategy;
    }
    return 0;
}
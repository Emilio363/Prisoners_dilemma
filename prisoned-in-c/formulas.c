#include <math.h>
#include <stdlib.h>
#include "game.h"
#include <stdio.h>
#include "parameters.h"


float fermi(float point1, float point2, ParamPtr par){    
    float prob = 1 / (1 + exp((point1 - point2) / par->k));
    return prob;
}

float H_x(int memory, ParamPtr par){
    if (par->max_memory == 0){
        return 1;
    }else{
        return 1-(1-par->beta)*memory/par->max_memory ;
    }
}

int incrementPoint(Cell_ptr player1, Cell_ptr player2, ParamPtr par){
    player1->point += oneGame_oneResult(player1, player2, par);
    return 0;
}

int changeStrategy(Cell_ptr player1, Cell_ptr player2, ParamPtr par){
    float thisrand = rand();
//    printf("maybe change");  //to debug
    
    float prob = H_x(player1->memory, par)*fermi(player1->point, player2->point, par);
    char (*newstrategy)() = player1->strategy;
    
    thisrand /= RAND_MAX; // to have a number between 0 and 1
//    printf(" %f, %f, %i \n", prob, thisrand, myrand); //to debug
    if (prob < thisrand){
//        printf("changing strategy\n"); //to debug
        newstrategy = player2->strategy;
    }
    if (newstrategy == player1->strategy){
        if (player1->memory<par->max_memory){
            player1->memory++;
        }
    }
    else{
        player1->memory = 0;
        player1->strategy = newstrategy;
    }
    return 0;
}
#include <sys/types.h>
#include <stdlib.h>
#include "parameters.h"

// ATTENTION: each strategy have to return 'C' or 'D'

char cooperate() {
    return 'C';
}

char defect() {
    return 'D';
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

char (*get_defect(void))(void){
    return defect;
}

char (*get_cooperate(void))(void){
    return cooperate;
}

u_int8_t * strategyColor(char (*strategy)()){
    u_int8_t * color = (u_int8_t *)malloc(3*sizeof(u_int8_t));
    if (strategy == cooperate){
        color[0] = 153; //azzurrino
        color[1] = 255;
        color[2] = 255;
    } 
    else if (strategy == defect){
        color[0] = 153; // bluino
        color[1] = 30;
        color[2] = 30;
    }
    else {
        color[0] = 255;
        color[1] = 0;
        color[2] = 0;
    }
    return color;
}
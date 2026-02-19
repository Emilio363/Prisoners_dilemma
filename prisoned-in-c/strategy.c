#include <sys/types.h>
#include <stdlib.h>

// ATTENTION: each strategy have to return 'C' or 'D'

char cooperate() {
    return 'C';
}

char defect() {
    return 'D';
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
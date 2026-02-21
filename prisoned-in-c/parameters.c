#include "parameters.h"
#include <stdlib.h>

ParamPtr standardParameters(){
    ParamPtr param = (ParamPtr)malloc(sizeof(Parameters));
    param->dim = 200;
    param->image_proportion = 4;
    param->iteration = 5000;
    param->image_step = 500;

    param->t = 1.05;
    param->r = 1;
    param->p = 0;
    param->s = 0;

    param->max_memory = 0;
    param->k = 1.05;
    param->beta = 0.5;

    return param;
}
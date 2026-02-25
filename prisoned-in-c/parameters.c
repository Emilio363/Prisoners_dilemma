#include "parameters.h"
#include <stdlib.h>

ParamPtr easyParameters(){
    ParamPtr param = (ParamPtr)malloc(sizeof(Parameters));
    param->dim = 20;
    param->image_proportion = 4;
    param->max_iteration = 500;
    param->actual_iteration = 0;
    param->image_step = 50;

    param->t = 1.05;
    param->r = 1;
    param->p = 0;
    param->s = 0;

    param->max_memory = 0;
    param->k = 0.1;
    param->beta = 0.5;

    return param;
}

ParamPtr standardParameters(){
    ParamPtr param = (ParamPtr)malloc(sizeof(Parameters));
    param->dim = 200;
    param->image_proportion = 4;
    param->max_iteration = 500;
    param->actual_iteration = 0;
    param->image_step = 50;

    param->t = 1.05;
    param->r = 1;
    param->p = 0;
    param->s = 0;

    param->max_memory = 0;
    param->k = 0.1;
    param->beta = 0.5;

    return param;
}

ParamPtr strongParameters(){
    ParamPtr param = (ParamPtr)malloc(sizeof(Parameters));
    param->dim = 200;
    param->image_proportion = 4;
    param->max_iteration = 10000;
    param->actual_iteration = 0;
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

ParamPtr funkyParameters(){
    ParamPtr param = (ParamPtr)malloc(sizeof(Parameters));
    param->dim = 50;
    param->image_proportion = 4;
    param->max_iteration = 10000;
    param->actual_iteration = 0;
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
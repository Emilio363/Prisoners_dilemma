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
    param->k = 0.1;
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
    param->k = 0.1;
    param->beta = 0.5;

    return param;
}

SirParamPtr easySirParameters(){
    SirParamPtr param = (SirParamPtr)malloc(sizeof(SIRParameters));
    param->dim = 20;
    param->image_proportion = 4;
    param->max_iteration = 500;
    param->image_step = 50;

    param->infected_time = 8;
    param->resistent_time = 8;
    param->propagation_ratio = 0.9;

    param->initial_infected_ratio = 0.0002;
    param->reinfected = 0;

    return param;
}

SirParamPtr stdInSIR(ParamPtr param){
    SirParamPtr sirparam = (SirParamPtr)malloc(sizeof(SIRParameters));
    sirparam->dim = param->dim;
    sirparam->image_proportion = param->image_proportion;
    sirparam->max_iteration = param->max_iteration;
    sirparam->image_step = param->image_step;

    sirparam->infected_time = 8;
    sirparam->resistent_time = 8;
    sirparam->propagation_ratio = 0.9;

    sirparam->initial_infected_ratio = 0.0002;
    sirparam->reinfected = 0;

    return sirparam;

}

ParamPtr stdOutSIR(SirParamPtr param){
    ParamPtr par = (ParamPtr)malloc(sizeof(Parameters));
    par->dim = param->dim;
    par->image_proportion = param->image_proportion;
    par->max_iteration = param->max_iteration;
    par->image_step = param->image_step;

    par->t = 1.05;
    par->r = 1;
    par->p = 0;
    par->s = 0;

    par->max_memory = 0;
    par->k = 0.1;
    par->beta = 0.5;

    return par;
}
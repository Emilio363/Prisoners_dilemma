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

FireParamPtr easyFireParameters(){
    FireParamPtr param = (FireParamPtr)malloc(sizeof(FireParameters));
    param->dim = 20;
    param->image_proportion = 4;
    param->max_iteration = 500;
    param->image_step = 50;

    // param->max_grou = 10; //max grouth of a cell
    // param->burning_time = 3;
    // param->burned_time = 6;

    param->propagation_ratio = 0.5; //chance for a cell to be burned if a neighboor is burning
    param->wind_direction = (int *)malloc(2*sizeof(int));
    param->wind_direction[0] = 0;
    param->wind_direction[1] = 1;

    param->spontaneus_burning = 0.000; //chance for a cell to spontaneus burning

    param->initial_burn_ratio = 0.005;
    param->initial_tree_ratio = 0.7;

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

FireParamPtr stdInFire(ParamPtr param){
    FireParamPtr fireparam = (FireParamPtr)malloc(sizeof(FireParameters));
    fireparam->dim = param->dim;
    fireparam->image_proportion = param->image_proportion;
    fireparam->max_iteration = param->max_iteration;
    fireparam->image_step = param->image_step;

    // fireparam->max_grou = 10; //max grouth of a cell
    // fireparam->burning_time = 3;
    // fireparam->burned_time = 6;

    fireparam->propagation_ratio = 0.5; //chance for a cell to be burned if a neighboor is burning
    fireparam->wind_direction = (int *)malloc(2*sizeof(int)); 
    fireparam->wind_direction[0] = 0;
    fireparam->wind_direction[1] = 1;

    fireparam->spontaneus_burning = 0.000; //chance for a cell to spontaneus burning

    fireparam->initial_burn_ratio = 0.000;
    fireparam->initial_tree_ratio = 0.7;

    return fireparam;
}

ParamPtr stdOutFire(FireParamPtr param){
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

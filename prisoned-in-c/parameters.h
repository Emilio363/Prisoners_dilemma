#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

struct Param
{
    int dim;
    int max_iteration;
    int actual_iteration;
    int image_proportion;
    int image_step;

    double t; //1<T<2 il guadagno ottenuto dal aver tradito l'avversario
    double r; // il guadagno dalla collaborazione
    double p; //il guadagno dal tradimento reciproco
    double s; //il guadagno se si viene traditi mentre si collabora

    int max_memory;
    double k;
    double beta;
};

typedef struct Param Parameters;
typedef struct Param * ParamPtr;

struct SIRParam
{
    int dim;
    int max_iteration;
    int image_proportion; //dimension in pixel of a cell in the immage
    int image_step;

    int infected_time;
    int resistent_time;
    double propagation_ratio; //probability for a cell to be infected if a neighboor is infect

    double initial_infected_ratio;
    int reinfected;
};

typedef struct SIRParam SIRParameters;
typedef struct SIRParam * SirParamPtr;

ParamPtr easyParameters();

ParamPtr standardParameters();

ParamPtr strongParameters();

ParamPtr funkyParameters();

SirParamPtr easySirParameters();

SirParamPtr stdInSIR(ParamPtr param);

ParamPtr stdOutSIR(SirParamPtr param);
#endif
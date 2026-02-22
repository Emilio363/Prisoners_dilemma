#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

struct Param
{
    int dim;
    int iteration;
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


ParamPtr easyParameters();
ParamPtr standardParameters();
ParamPtr strongParameters();


#endif
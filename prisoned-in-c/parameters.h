#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

struct Param {
    int dim;
    int image_proportion;
    int iteration;
    int image_step;

    float t; //1<T<2 il guadagno ottenuto dal aver tradito l'avversario
    float r; // il guadagno dalla collaborazione
    float p; //il guadagno dal tradimento reciproco
    float s; //il guadagno se si viene traditi mentre si collabora

    int max_memory;
    float k;
    float beta;
};

typedef struct Param Parameters;
typedef struct Param * ParamPtr ;

ParamPtr standardParameters();

#endif
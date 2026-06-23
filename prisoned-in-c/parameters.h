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

struct FireParam
{
    int dim;
    int max_iteration;
    int image_proportion;
    int image_step;

    // int max_grou; //max grouth of a cell
    // int burning_time;
    // int burned_time;

    double propagation_ratio; //chance for a cell to be burned if a neighboor is burning
    int * wind_direction; // West (-1, 0), Est (1, 0), South(0, -1)
// SW (-1, -1), SE (1, -1), North (0, 1), NW (-1, 1), NE(1, 1)
    double ** propagation_matrix;
    double spontaneus_burning; //chance for a cell to spontaneus burning

    double initial_burn_ratio;
    double initial_tree_ratio;
};

typedef struct FireParam FireParameters;
typedef struct FireParam * FireParamPtr;

struct IsingParam
{
    int dim;
    int max_iteration;
    int image_proportion;
    int image_step;

    double temperature;      // T
    double coupling;         // J
    double magnetic_field;   // h

    double hamiltonian;
    int step_iteration;

    double initial_ratio; // percentuale iniziale di spin +1
    int periodic_boundary;   // 0 = aperto, 1 = periodico
};

typedef struct IsingParam IsingParameters;
typedef struct IsingParam * IsingParamPtr;


ParamPtr easyParameters();
ParamPtr standardParameters();
ParamPtr strongParameters();
ParamPtr funkyParameters();

SirParamPtr easySirParameters();
FireParamPtr easyFireParameters();
IsingParamPtr isingParam();

double ** firePropMatrix(int * wind, double ratio);

SirParamPtr stdInSIR(ParamPtr param);
ParamPtr stdOutSIR(SirParamPtr param);
FireParamPtr stdInFire(ParamPtr param);
ParamPtr stdOutFire(FireParamPtr param);

#endif
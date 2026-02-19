#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <sys/types.h>

char cooperate();

char defect();

u_int8_t * strategyColor(char (*strategy)());

#endif
#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <sys/types.h>

char cooperate();

char defect();

char (*randomStrategy(void))(void);

char (*get_defect(void))(void);

char (*get_cooperate(void))(void);


u_int8_t * strategyColor(char (*strategy)());

#endif
#ifndef _FORMULAS_H_
#define _FORMULAS_H_

#include "parameters.h"
#include "game.h"

int incrementPoint(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

int changeStrategy(Cell_ptr player1, Cell_ptr player2, ParamPtr param, float thisrand);

float fermi(float point1, float point2, ParamPtr param);

u_int32_t xorshift32(u_int32_t x);

double norm(int * vec);

float H_x(int memory, ParamPtr param);

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

#endif
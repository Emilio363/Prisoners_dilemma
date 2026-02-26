#ifndef _FORMULAS_H_
#define _FORMULAS_H_

int incrementPoint(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

int changeStrategy(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

float fermi(float point1, float point2, ParamPtr param);

float H_x(int memory, ParamPtr param);

float oneGame_oneResult(Cell_ptr player1, Cell_ptr player2, ParamPtr param);

#endif
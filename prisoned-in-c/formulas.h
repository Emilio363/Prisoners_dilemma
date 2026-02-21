#ifndef _FORMULAS_H_
#define _FORMULAS_H_

int incrementPoint(Cell_ptr player1, Cell_ptr player2, ParamPtr par);

int changeStrategy(Cell_ptr player1, Cell_ptr player2, ParamPtr par);

float fermi(float point1, float point2, ParamPtr par);

float H_x(int memory, ParamPtr par);

#endif
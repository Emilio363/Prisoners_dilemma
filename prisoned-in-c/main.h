#ifndef _MAIN_C
#define _MAIN_C

#include "parameters.h"
#include "game.h"

void stampStrategies(ParamPtr param, Cell_ptr ** mat);
void stamPoints(ParamPtr param, Cell_ptr ** mat);
void stampMemory(ParamPtr param, Cell_ptr ** mat);
int printMatrix(ParamPtr param, Cell_ptr ** mat, char * image_path);
void NewPrintMatrix(ParamPtr param, Cell_ptr ** Cells, int iteration);
float evalCoopPercent(ParamPtr param, Cell_ptr ** Cells);
void freeMatrix(Cell_ptr **Cells, int dim);


#endif
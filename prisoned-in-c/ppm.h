#ifndef _PPM_H
#define _PPM_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "ppm.h"
#include "game.h"

struct _netpbm_image {
  int headerSize; // Dimensione dell'intestazione
  int size; //dimensione totale del file immagine
  int height; // altezza e larghezza dell'immagine
  int width;
  FILE * fd; //puntatore al file immagine
  char * data; //dati da salvare
};

typedef struct _netpbm_image ppm_str;
typedef struct _netpbm_image * ppm_ptr;

int createPPM(char * image_path, int height, int widht, ppm_ptr img);

int close_image(ppm_ptr img);

void _write_color (ppm_ptr img, int i, int j, u_int8_t * colors);


int CellsMatrixinPPM(int dim, Cell_ptr matrix[dim][dim], ppm_ptr image);

u_int8_t * testColor(int col, int row);

u_int8_t * _pixel_color(int widht, int height, int dim, Cell_ptr Cells[dim][dim], ppm_ptr image);

#endif
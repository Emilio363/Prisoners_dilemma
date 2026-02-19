#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "ppm.h"
#include "game.h"
#include "strategy.h"
#include "parameters.h"


int close_image(ppm_ptr img)
{
  if (img == NULL) {
    return -1;
  }
  munmap(img->data, img->size);
  fclose(img->fd);
  return 0;
}

// da usare per creare immagini vuote, da riempire successivamente
// Nella creazione viene già inclusa l'intestazione quindi non serve specificarla nella
// chiamata di funzione
int createPPM(char * image_path, int height, int widht, ppm_ptr img){
    img->fd = fopen(image_path, "w+");
    img->height = height;
    img->width = widht;
    if (img->fd == NULL) { //non esiste il path
        printf("Errore nella creazione dell'immagine di destinazione");
        return -1;
    }
    // carico l'intestazione nel file e salvo in "HeaderSize" 
    //la dimensione dei caratteri che ho inserito
    int headerSize= fprintf(img->fd, "P6\n %d %d\n 255\n", img->width, img->height);
    if (headerSize<=0){
        printf("Errore nella creazione dell'intestazione");
        return -2;
    }
    img->size = img->width*img->height*3*sizeof(__u_char) + headerSize; 
    //dimensione totale del file che creiamo
    img->headerSize= headerSize; //servirà per sapere da dove cominciare a immettere i dati

    int err = ftruncate(fileno(img->fd),img->size);
    if (err != 0)
    {
        printf("Errore nella modifica della dimensione del file");
        return -3;
    }

    img->data = mmap(NULL, img->size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(img->fd), 0);
    if (img->data == MAP_FAILED) {
        fclose(img->fd);
        printf("Errore nella modifica della dimensione del file");
        return -3;
    }
    return 0;
}

// dato un colore del pixel lo assegno
void _write_color (ppm_ptr img, int row, int col, u_int8_t * colors){
    img->data[img->headerSize + 3*(col*img->width+row)] = colors[0];
    img->data[img->headerSize + 3*(col*img->width+row)+1] = colors[1];
    img->data[img->headerSize + 3*(col*img->width+row)+2] = colors[2];
    free(colors);
}

// Funzione che da una matrice di celle crea la corretta immagine PPM
int CellsMatrixinPPM(int dim, Cell_ptr matrix[dim][dim], ppm_ptr image){
    
    int height = image->height;
    int width = image->width;

    for(int col = 0; col <  width; col++){
        for(int row = 0; row < height; row++){
            // trovo il colore forse giusto
//            printf("il colore del pixel %i %i ", row, col);
            u_int8_t * color = _pixel_color(col, row, dim, matrix, image);
            // u_int8_t * color = testColor(col, row);
            // inserisco i valore trovato
            _write_color(image, row, col, color);
            // free(color);
        }
    }
    return 1;
}

// crea un immagine a bande orizzontali blu e verdi
u_int8_t * testColor(int col, int row){
    u_int8_t * color = (u_int8_t *)malloc(3*sizeof(u_int8_t));
    if (col/10%2 == 0){
        printf("this color");
        color[0] = 0;
        color[1] = 0;
        color[2] = 255;
    }
    else {
        printf("other color");
        color[0] = 0;
        color[1] = 255;
        color[2] = 0;
    }
    return color;
}

// dato un pixel posso calcolare il colore del pixel
u_int8_t * _pixel_color(int widht, int height, int dim, Cell_ptr Cells[dim][dim], ppm_ptr image){
    double distw = (double)widht/image->width; 
    // proporzione della distanza del pixel
    // in modo da poterla rapportare con la matrice
    double disth = (double)height/image->height;
    u_int8_t * worngcolor = (u_int8_t *)malloc(3*sizeof(u_int8_t));

    if (distw>1 || distw<0){
        printf("errore larghezza pixel\n");
        return worngcolor;
    }
    if (disth>1 || disth<0){
        printf("errore altezza pixel\n");
        return worngcolor;
    }
    int intdistw = distw*dim;
    int intdisth = disth*dim;

//    printf("viene dalla cella %i %i\n",intdisth, intdistw);
    u_int8_t * color = strategyColor(Cells[intdisth][intdistw]->strategy);
    return color;
}
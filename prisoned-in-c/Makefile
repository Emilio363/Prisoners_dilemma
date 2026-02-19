CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fopenmp

HEADERS = formulas.h game.h strategy.h ppm.h parameters.h
OBJECTS = formulas.o game.o strategy.o ppm.o parameters.o main.o 

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^ -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean all

clean:
	rm -f *.o
	rm -f *.ppm
	rm -f main

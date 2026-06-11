CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fopenmp
LIBFLAG = -O3 -Wall -pedantic -std=c17 -fopenmp -fPIC -shared

HEADERS = formulas.h game.h strategy.h ppm.h parameters.h miscellaneous.h
OBJECTS = formulas.o game.o strategy.o ppm.o parameters.o miscellaneous.o main.o
LIBRARY = formulas.so game.so strategy.so ppm.so parameters.so miscellaneous.so main.so

all: main library

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^ -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean all

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.ppm
	rm -f main

cleanso:
	rm -f *.so

library:${LIBRARY}
%.so: %.c ${HEADERS}
	${CC} ${LIBFLAG} -o $@ $<
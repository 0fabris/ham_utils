#Makefile to build the demo of the WWLocator
CC = gcc

FLAG = -g
DEMOFLAG = -lm

all: demo_build clean
	@echo "All Done!"

demo_build: coord_build
	${CC} ${FLAG} ${DEMOFLAG} demo.c coord.o -o built_demo
	
coord_build:
	${CC} ${FLAG} -c coord.c 

clean:
	rm *.o

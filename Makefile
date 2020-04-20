#Makefile to build the demo of the WWLocator
CC = gcc

FLAG = -g
DEMOFLAG = -lm

all: demo_build tle_demo_build clean
	@echo "All Done!"

demo_build: coord_build
	@cd wwlocator; \
	${CC} ${FLAG} ${DEMOFLAG} demo.c coord.o -o built_demo

coord_build:
	@cd wwlocator; \
	${CC} ${FLAG} -c coord.c

tle_demo_build: tle_build
	@cd tle; \
	${CC} ${FLAG} ${DEMOFLAG} tledemo.c tle.o -o built_demo

tle_build:
	@cd tle; \
	${CC} ${FLAG} -c tle.c 
clean:
	rm tle/*.o
	rm wwlocator/*.o

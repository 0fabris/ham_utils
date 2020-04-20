#ifndef _COORD_H
#define _COORD_H

typedef struct {
	char* locator;
	float lon;
	float lat;
} coord;

coord* getCoordinate(char*);
char* getLocator(float,float);

#endif

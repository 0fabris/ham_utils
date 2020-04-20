#include <stdio.h>
#include <stdlib.h>

#include "coord.h"

//Demo: insert a locator in stdin and it will give you the coordinates

int main(){
        char* st = (char*)malloc(7*sizeof(char));
        
        scanf("%s",st);
        
        coord* pnt = getCoordinate(st);
        
	printf("coord %s: (%.3f,%.3f)\n\n",pnt->locator,pnt->lat,pnt->lon);

}

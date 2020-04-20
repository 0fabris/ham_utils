#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#include "coord.h"

coord* getCoordinate(char* loc){
	coord* co = NULL;
	
	//SAMPLE: AB123CD
	
	//Check locator is 6 char long
	if(loc[6] == '\0'){
	
		//Convert Lowercase to Uppercase
		loc[0] = toupper(loc[0]);
		loc[1] = toupper(loc[1]);
		loc[4] = toupper(loc[4]);
		loc[5] = toupper(loc[5]);

		//creating coord object
		co = (coord*)malloc(sizeof(coord));
		co->locator = (char*)malloc(7*sizeof(char));
		strcpy(co->locator,loc);
		//Latitude and longitude from first 2 characters
		for(int i = -90,c = 0; i < 90; i+=10, c++)
		{
			if(loc[0] == ('A'+c))
				co->lon = i*2.0;
			if(loc[1] == ('A'+c))
				co->lat = i;
		}
		//Number Adjustment 0->9 pass 2-lon, 1-lat
		co->lon += ((loc[2]-'0')*2.0);
		co->lat += ((loc[3]-'0')*1.0);
		
		//Last chars Adjustment A->X pass 5'-lon, 2.5'-lat
		co->lon += ((loc[4] - 'A') * (5.0/60));
		co->lat += ((loc[5] - 'A') * (2.5/60));
	}
	return co;
}

char* getLocator(float lat, float lon){
	//Creating the string
	char* st = (char*)malloc(7*sizeof(char));
	
	//Guess the first 2 chars
	for(int i = 160,c = 0; i >=-180; i-=20, c++){
		if(lon>((float)i)){
			st[0] = 'R'-c;
        		lon-=(float)i;
			break;
		}
	}
	
	for(int i = 80,c = 0; i >= -90; i-=10, c++){
		if(lat>((float)i)){
                	st[1] = 'R'-c;
			lat-=(float)i;
			break;
		}
	}
	
	//First 2 chars OK, now 2 numbers
	st[2] = '0' + ((int)lon/2);
	st[3] = '0' + ((int)lat/1);

	lon -= 2.0f * ((int)lon/2);
	lat -= 1.0f * ((int)lat/1);
	
	//2 numbers OK, now last 2 chars

	st[4] = 'A' + (int)roundf(10*(60.0f*lon/5.0f))/10;
	st[5] = 'A' + (int)roundf(10*(60.0f*lat/2.5f))/10;
	st[6] = '\0';
	//All OK
	return st;
}

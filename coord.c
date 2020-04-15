#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "coord.h"

coord* getCoordinate(char* loc){
	coord* co = NULL;
	
	//SAMPLE: AB123CD
	
	//Check locator is 6 char long
	if(loc[6] == '\0'){
	
		//Convert Lowercase to Uppercase
		if(loc[0]>='a' && loc[0] <= 'z')
			loc[0] = loc[0] - 'a' + 'A';
		if(loc[1]>='a' && loc[1] <= 'z')
			loc[1] = loc[1] - 'a' + 'A';
		if(loc[4]>='a' && loc[4] <= 'z')
                        loc[4] = loc[4] - 'a' + 'A';
                if(loc[5]>='a' && loc[5] <= 'z') 
                        loc[5] = loc[5] - 'a' + 'A';
		
		//creating coord object
		co = (coord*)malloc(sizeof(coord));
		co->locator = (char*)malloc(7*sizeof(char));
		strcpy(co->locator,loc);
		//Latitude and longitude from first 2 characters
		for(int i = -180,c = 0; i < 180; i+=20, c++)
			if(loc[0] == ('A'+c))
				co->lon = i;
		for(int i = -90,c = 0; i < 90; i+=10, c++)
			if(loc[1] == ('A'+c))
				co->lat = i;
		
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

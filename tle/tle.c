#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "tle.h"

//Init of the TLE
tle* initTLE()
{
	tle* t = (tle*)malloc(sizeof(tle));
	t->name = (char*)malloc((ROWSIZE+1)*sizeof(char));
        strcpy(t->name,"");
	t->sat_catnumber = 0;
        t->sat_classification = Secret;
        t->launch_year = 0;
        t->launch_year_number = 0;
        t->launch_piece = (char*)malloc(4*sizeof(char));
        strcpy(t->launch_piece,"");
	t->epoch_year = 0;
        t->epoch_day= 0.0f;
        t->ballistic_coefficient = 0.0f;
        t->second_derivative = 0.0f;
        t->tle_counter = 0;
        t->inclination = 0.0f;
        t->asc_node = 0.0f;
        t->eccentricity = 0.0f;
        t->perigee_argument = 0.0f;
        t->mean_anomaly = 0.0f;	
	t->rev_number_epoch = 0;
	return t;
}

//reads TLE from file
tle* readFile(char* fname)
{
	tle* t = initTLE();
	FILE* fp = fopen(fname,"r");
	if(fp == NULL)
		return t;

	char buffer[ROWSIZE+1] = "";
	int c = 0;
	while(!feof(fp) && c++<3)
	{
		fgets(buffer,ROWSIZE+2,fp);
		
		//Remove newline chars
		for(int i = ROWSIZE; i>=0; i--)
			if(buffer[i] == '\r' || buffer[i] == '\n')
				buffer[i] = '\0';

		parseRow(buffer,t);
	}
	fclose(fp);
	return t;
}

//Catch the content of the TLE Rows
void parseRow(char* string, tle* data)
{
	if(isupper(string[0]) || islower(string[0]))
	{
		//string is name of the satellite
		strcpy(data->name,string);
	}
	else if (string[0] == '1')
	{
		//Doing second row
		//%*d %5d%c %2d%3d%3s %2d%12f %10f %8f %*f %*d %4d%1d
		sscanf(string,"%*d %5d%c %2d%3d%3s %2d%12f %10f %*8s %*8s %*1d %4d%*d",&data->sat_catnumber,&data->sat_classification, &data->launch_year, &data->launch_year_number, data->launch_piece, &data->epoch_year, &data->epoch_day,&data->ballistic_coefficient, &data->tle_counter);				
	}
	else if (string[0] == '2')
	{
		//Doing last row
		int tmp;
		sscanf(string,"%*d %*5d %8f %8f %7d %8f %8f %11f%5d%*d",&data->inclination, &data->asc_node, &tmp, &data->perigee_argument, &data->mean_anomaly, &data->mean_motion, &data->rev_number_epoch);
	data->eccentricity = tmp/10000000.0;
	}
	else
		printf("String format not recognised\n");
}


//Prints given TLE data
void printTLEData(tle* t)
{
	printf("--- %s ---\n\n\n",t->name);

	printf("Satellite Catalog nr: %d\n",t->sat_catnumber);
        printf("Satellite Classification: %c\n",t->sat_classification);
        printf("Launch Year: %d\n",t->launch_year);
        printf("Launch number of that year: %d\n",t->launch_year_number);
        printf("Launch piece of that year: %s\n",t->launch_piece);

        printf("\nEpoch: %d\n",t->epoch_year);
        printf("Epoch day: %.2f\n",t->epoch_day);
        printf("\nBal. Coeff.: %.10f\n",t->ballistic_coefficient);
        printf("2nd derivative: %.2f\n",t->second_derivative);
        printf("\nTLE Counter: %d\n",t->tle_counter);
        //t->checksum;
        printf("Inclination: %.2f\n",t->inclination);
        printf("Ascension Node: %.2f\n",t->asc_node);
        printf("Eccentricity: %.8f\n",t->eccentricity);
        printf("Perigee Arg.: %.2f\n",t->perigee_argument);
        printf("Mean Anomaly: %.2f\n",t->mean_anomaly);
	printf("Rev. Nr Epoch: %d\n",t->rev_number_epoch);
}

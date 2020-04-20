#ifndef _TLE_H
#define _TLE_H

#define ROWSIZE 70

enum classification {
	Unclassified = 'U', 
	Classified = 'C',
	Secret = 'S'
};

typedef struct {
	char* name;
	int sat_catnumber;
	enum classification sat_classification;
	int launch_year;
	int launch_year_number;
	char* launch_piece;
	int epoch_year;
	float epoch_day;
	float ballistic_coefficient;
	float second_derivative;
	//int ephermeris_type;
	int tle_counter;
	//int checksum;
	float inclination;
	float asc_node;
	float eccentricity;
	float perigee_argument;
	float mean_anomaly;
	float mean_motion;
	int rev_number_epoch;
} tle;

tle* initTLE();

void parseRow(char*, tle*);

void printTLEData(tle*);

tle* readFile(char*);

#endif

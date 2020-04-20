#include <stdio.h>

#include "tle.h"

int main(){
	tle* t = initTLE();
	
	parseRow("ISS (ZARYA)",t);
	parseRow("1 25544U 98067A   20111.37213951  .00005628  00000-0  10909-3 0  9999",t);
	parseRow("2 25544  51.6434 274.6148 0001845 175.3305 266.0242 15.49303222223054",t);
	//parseRow("33",t);
	printTLEData(t);
	
	tle* t1 = readFile("iss.txt");
	printTLEData(t1);

	return 0;
}

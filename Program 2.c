//Adam Buerger
//Programming Assignment 2 CSC 362
//calculates a group of cities' individual population density and livability (as well as the city with the best libabilty and the average of the group) based on input from a file

#include "header.h"		//include custom header file containing any libraries and function prototypes needed by this program
/*			Contents of header.h

#include <stdlib.h>
#include <stdio.h>

#define POLCO 1112.2//define pollution coefficient for use in compute()
#define TRACO 2.13	//define traffic coefficient for use in compute()
#define CRICO 924.5	//define crime coefficient for use in compute()
#define EXPCO 1217.1//define expense coefficient for use in compute()
#define LIVCO 13.81	//define livability coefficient for use in compute()

int input(FILE*, char[], int*, int*, int*, int*, int*, int*);	//scans for and stores a city's name, population, area(in swaure miles), pollution level, crime level, expense level, and number of near by highways, to be used in populationDensity() and compute()
void output(char[], double, double);							//prints the name, population density, and livability of the current city.
void update(int*, double*, double*, char[], double, char[]);	//determines which city has the best livability and adds the current city's livability to the total livability of all cities put together for averaging in summary()
void summary(char[], double, int, double);						//outputs the best city's name and livability as well as the total cities scanned and what their average livability is

double populationDensity(int, int);								//computes population density (population/square mileage)
double compute(double, int, double, int, double, int, double, int, double, double*, double*, double*, double*); //computes and stores a city's pullution value, traffic value, crime value, and expense value values
double livability(double, double, double, double, double);		//computes and returns the livability of a city based on values from compute()
*/

void main() {
	int
		population = 0,		//population of the city
		squareMileage = 0,	//area of the city
		pollution = 0,		//ammount of pollution in the city
		crime = 0,			//ammounnt of crime in the city
		expense = 0,		//value of how expensive the city is
		highways = 0,		//number of major highways near the city
		numOfCities = 0;	//stores the number of scanned cities
	double
		popDensity = 0,		//to be calculated by populationDensity()
		pollutionValue = 0,	//this and the following three doubles are to be calculated by compute()
		trafficValue = 0,
		crimeValue = 0,
		expenseValue = 0,
		livabilityValue = 0,//used to store a city's calculated livability for further use
		valueOfCities = 0,	//holds the total livability of all cities
		bestCityValue = 0;	//holds the best livability value of scanned cities
	char
		name[30] = "",		//name of the city
		bestCity[30] = "";	//holds the name of the city with the best livability;
	FILE * file;						//declare the file variable
	file = fopen("cities2-1.txt", "r");	//set the file to one of the city text files
	printf("Name\t\t\tPop. Density\tLivability\n");														//print the framework of how the information is output to the console
	while (input(file, name, &population, &squareMileage, &pollution, &crime, &expense, &highways) != EOF) {
		//run the loop while there are still cities to be scanned
		popDensity = populationDensity(population, squareMileage);										//calculate and store the population density
		compute(popDensity,																				//sends the population density to copute()
			pollution, POLCO,																			//sends the pollution level and the pollution coefficient to compute()
			highways, TRACO,																			//sends the number of highways and the traffic coefficient to compute()
			crime, CRICO,																				//sends to the crime level and crime coefficient to compute()
			expense, EXPCO,																				//sends to the expense level and expense coefficient to compute()
			&pollutionValue, &trafficValue, &crimeValue, &expenseValue);								//sends variables to compute to store restults of computations done by the function
		livabilityValue = livability(pollutionValue, trafficValue, crimeValue, expenseValue, LIVCO);	//calculates and stores the livability of the current city given the output of compute() and the livability coefficient
		output(name, popDensity, livabilityValue);														//prints the name, population density, and livability of the current city
		update(&numOfCities, &valueOfCities, &bestCityValue, bestCity, livabilityValue, name);			//checks the current city against the city with the best livability
	}
	summary(bestCity, bestCityValue, numOfCities, valueOfCities);	//prints the name and livability of the best city, the total number of cities checked, and the average livabilt of those cities
	fclose(file);													//closes the file reader
}
/*			Output when file reads cities2-1.txt:

Name                    Pop. Density    Livability
Atlanta                 451.209         52.361
Boston                  517.143         36.145
Cincinnati              298.633         72.542
Dallas                  251.294         77.090
Las_Vegas               158.677         83.461
Los_Angeles             576.611         16.670
Minneapolis             303.487         72.201
New_York_City           730.751         6.358
Seattle                 370.022         64.140
Washington_DC           493.871         41.380
Best city: Las_Vegas, with a livability of 83.461
The 10 cities have an average livability of 52.235

			Contents of mathFunctions.c

double populationDensity(int pop, int sqrMiles) {
	//computes and returns population density (population/square mileage)
	return (double)pop / (double)sqrMiles;
}
void compute(double density,									//takes in population density
	int pollution, double POLCO,								//takes in population and population coefficient
	int highways, double TRACO,									//takes in number of highways and traffic coefficent
	int crime, double CRICO,									//takes in crime and crime coefficent
	int expense, double EXPCO,									//takes in expense and expense coefficient
	double* polV, double* traV, double* criV, double* expV) {	//takes in values to store the results of computations

	*polV = (pollution * density) / POLCO;						//computes and stores the pollution value
	*traV = (density * TRACO) / highways;						//computes and stores the traffic value
	*criV = (crime * density) / CRICO;							//computes and stores the crime value
	*expV = (expense * density) / EXPCO;						//computes and stores the expense value
}
double livability(double polV, double traV, double criV, double expV, double LIVCO) {
	//computes and returns the livability of a city based on values stored by compute()
	return 100 - (polV + traV + criV + expV) / LIVCO;
}

			Contents of ioFunctions.c

#include <stdio.h>
int input(FILE *file, char name[], int *population, int *squareMileage,	int *pollution,	int *crime,	int *expense,	int *highways) {
	//takes in a file, string, and six ints to store scanned values
	return fscanf(file, "%s %d %d %d %d %d %d", name, population, squareMileage, pollution, crime, expense, highways);
}
void output(char name[], double density, double livability) {
	//print the name, population density, and livability of a city
	printf("%-10s\t\t%-10.3f\t%-10.3f\n", name, density, livability);
}
void summary(char name[], double livability, int numOfCities, double valueOfCities) {
	//prints the name and livability of the city with the highest livability as well as the average livability of all cities checked and the number of cities averaged
	printf("Best city: %s, with a livability of %.3f\n", name, livability);						//print the name and livability of the city with the best livability
	valueOfCities /= numOfCities;																//compute the average livability
	printf("The %d cities have an average livability of %.3f\n", numOfCities, valueOfCities);	//print the number of cities and the average livability
}
void update(int* numOfCities, double* valueOfCities, double* bestCity, char bestName[], double currentLivability, char currentName[]) {
	//determines the best city by livability and stores the best values
	*numOfCities += 1;						//add 1 to the total city count
	*valueOfCities += currentLivability;	//add the current city's livability to the livability of all cities put together
	if (*bestCity < currentLivability) {	//if the current city's livability is better than the best city's livability...
		strcpy(bestName, currentName);		//the name of the best city becomes the name of the current city
		*bestCity = currentLivability;		//and the livability of the best city becomes the livability of the current city
	}
}
*/
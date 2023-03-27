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
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
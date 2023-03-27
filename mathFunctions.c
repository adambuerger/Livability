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
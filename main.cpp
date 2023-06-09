#include "PriceGenerator.h"
#include <iostream>
#include <algorithm>
using namespace std;

void priceGeneratorSample(double initEquityPrice, unsigned numTimeStamps, double timeToExpiry, double drift, double volatility, int seed);
void printDouble(double s);

// Function to test option price generator with sample data
void priceGeneratorSample(double initEquityPrice, unsigned numTimeStamps, double timeToExpiry, double drift, double volatility, int seed) {
	// Define price generator object
	PriceGenerator pg(initEquityPrice, numTimeStamps, timeToExpiry, drift, volatility);

	vector<double> resultPrices = pg(seed); // call function and store in vector

	// Output result
	for_each(resultPrices.begin(), resultPrices.end(), printDouble);
	cout << endl << endl;
}

// Helper print function for std::for_each(.)
void printDouble(double s)
{
	cout << s << " ";
}

int main() {
	// Define sample parameters
	double initEquityPrice = 100.0;
	unsigned numTimeStamps = 12; // 5 years, quarterly time steps
	double timeToExpiry = 1.0; // aka time to maturity
	double drift = 0.025; // risk-free interest rate
	double volatility = 0.06;
	int seed = -106;

	priceGeneratorSample(initEquityPrice, numTimeStamps, timeToExpiry, drift, volatility, seed);
	
	return 0;
}

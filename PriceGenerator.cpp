#include "PriceGenerator.h"
#include <random>
#include <algorithm>	
#include <ctime>
#include <cmath>

using std::vector;
using std::mt19937_64;
using std::normal_distribution;
using std::exp;

PriceGenerator::PriceGenerator(double initEquityPrice, unsigned numTimeStamps, double timeToExpiry, double drift, double volatility) :
	// Initialize private members
	initEquityPrice_(initEquityPrice),
	numTimeSteps_(numTimeStamps),
	drift_(drift),
	volatility_(volatility),
	dt_(timeToExpiry / numTimeStamps) {}

vector<double> PriceGenerator::operator()(int seed) const { // Overloads () operator
	vector<double> v;

	mt19937_64 mtEngine(seed);
	normal_distribution<> nd;

	// Lambda function to return option price
	auto newPrice = [this](double prevPrice, double norm) {
		// prevPrice: price of previous equity in series
		// norm: random number drawn from normal dist.
		// formula = prevPrice * e^( ( (drift_ - ((volatility_ * volatility_) / 2.0) ) * dt_) + ( volatility_ * norm * sqrt(dt_) ) )

		double price = 0.0;

		// split up exponent of e to two parts
		double exp1 = ((drift_ - (volatility_ * volatility_) / 2) * dt_);
		double exp2 = volatility_ * norm * sqrt(dt_);

		price = prevPrice * exp(exp1 + exp2); // apply formula to generate option price

		return price;
	};

	v.push_back(initEquityPrice_); // add first stock price to vector
	double equityPrice = initEquityPrice_; // variable to store previous price

	for (int i = 1; i <= numTimeSteps_; ++i) {
		double norm = nd(mtEngine); // generate random number
		equityPrice = newPrice(equityPrice, norm); // generate equity price for next time step
		v.push_back(equityPrice); // append to vector
	}

	return v;
}




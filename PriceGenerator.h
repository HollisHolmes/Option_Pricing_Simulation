#ifndef PRICE_GENERATOR_H
#define PRICE_GENERATOR_H

#include<vector>

class PriceGenerator {
public:
	PriceGenerator(double initEquityPrice, unsigned numTimeStamps, double timeToExpiry, double drift, double volatility);
	std::vector<double> operator()(int seed) const;

private:
	double dt_; 
	const double initEquityPrice_;
	const int numTimeSteps_;
	const double drift_;
	const double volatility_;
};

#endif
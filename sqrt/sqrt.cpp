/*
 * Name             sqrt.cpp
 * Author           Krystal Hong
 * Date             8 September 2021
 * Description      Compute square root using Newton's method
 * Pledge           I pledge my honor that I have abided by the Stevens Honor System.
 */



#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon){
	double last_guess = num;
	double next_guess = (last_guess + num/last_guess)/2;
	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}
	if (num == 0 || num == 1){
		return num;
	}
	while(abs(last_guess - next_guess) > epsilon){
		last_guess = next_guess;
		next_guess = (last_guess + num/last_guess) / 2;

	}

	return next_guess;
}



int main (int argc, char *argv[]) {
	istringstream iss;
	double num;
	double epsilon;
	epsilon = 1e-7;

	if (argc > 3 || argc < 2){
		cerr << "Usage: " << argv[0]<<" <value> [epsilon]" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> num)){
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}
	iss.clear();

	if(argc == 3){
		iss.str(argv[2]);
		if(!(iss >> epsilon) | (epsilon <= 0)){
			cerr << "Error: Epsilon argument must be a positive double."<< endl;
			return 1;
		}

	}
	iss.clear();

	cout.precision(8);
	cout << fixed << sqrt(num, epsilon)<< endl;



	return 0;
}


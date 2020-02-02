#pragma once
#include <iostream>
#include <math.h>
#include "GeneralNumericalSettings.hpp"


struct SolDerivation {
	myDouble *xDeriv;
	myDouble *yDeriv;
	int dim;
};

//Computes the k-th-derivation between n values of an array
//returns a SolDerivation struct
//remember deleting it!
//
//input arrays need to be equaly spaced.
//always returns a k-4-dim array
//1st and 2nd Order accurracy: h^4
//3rd and 4th Order accurracy: h^2
SolDerivation derivArr(int derivOrder, myDouble x[], myDouble y[], int numOfPoints, myDouble stepSize);

//returns the maximum of a given array
// always returns a max>=0
myDouble maxArr(myDouble arr[], int dim);

//calculates the maximum of the n-th Derivation of given functionpoints
//only implemented for numbers from 1 to 4
//on error returns 0
myDouble maxDeriv(int derivOrder, myDouble x[], myDouble y[], int dim, myDouble stepSize);

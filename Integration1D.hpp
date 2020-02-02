#pragma once
#include <math.h>
#include <functional>
#include <iostream>
#include "GeneralNumericalSettings.hpp" //used for typedefs
#include "matrices.hpp"
#include "Derivation.hpp"


// a class which is given to a integration routine
// contains all neccessary information to integrate a function
class Integrand1D
{
private:
	int numDataPoints;
	myDouble stepSize;
	myDouble begin;
	myDouble end;
	myDouble *dataX;
	myDouble *dataY;
	std::function<myDouble(myDouble)> f;
public:
	//Constructor with given interval
	Integrand1D(int numDataPoints, myDouble begin,myDouble end,f_myDouble const f);
	//Constructor with given startpoint and stepsize
	Integrand1D(int numDataPoints, myDouble begin,f_myDouble const f, myDouble stepSize);
	//Copy constructor
	Integrand1D(Integrand1D const &Int);
	//Destructor
	~Integrand1D();
	myDouble getBegin();
	myDouble getEnd();
	int getNumDataPoints();
	myDouble getStepSize();
	myDouble* getDataX();
	myDouble* getDataY();
	f_myDouble getFunc();
	void coutData();
};

// a structure which is the solution of an integration
struct SolutionIntegration {
	myDouble solution = 0;
	myDouble error = 0;
};


typedef std::function<SolutionIntegration(Integrand1D)> f_Integrator;

//fills an Array with a given function 'f', from 'start' 'numberPoints' times with 'stepsize' 
//returns a pointer to the array on heap
// remember deleting it!
myDouble* fillArr(f_myDouble const &f, myDouble start, int numberPoints, myDouble stepsize);

//Integration Method with trapezoidal rule
//takes an Integrand
//returns a solutionIntegration
SolutionIntegration trapezoidalRule(Integrand1D val);

//Integration Method with Newton Cotes 2
//takes an Integrand
// the dimension of the data-Arrays has to be 2n+1, for n � N
//returns a solutionIntegration
SolutionIntegration newtonCotes2(Integrand1D val);

//Integration Method with Simpsons 3/8 Rule
//takes an Integrand
// the dimension of the data-Arrays has to be 3n+1, for n � N
//returns a solutionIntegration
SolutionIntegration simpsons3_8(Integrand1D val);

//Integration Method with Euler-Maclaurin
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration eulerMaclaurin(Integrand1D val);

//Integration Method with Gauss-Legendre 2
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration gaussLegendre2(Integrand1D val);

//Integration Method with Gauss-Legendre 4
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration gaussLegendre4(Integrand1D val);

//Integration Method with Gauss-Legendre 8
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration gaussLegendre8(Integrand1D val);


//Integration Method with Splines
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration splinesInteg(Integrand1D val);
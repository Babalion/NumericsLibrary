#include "Derivation.hpp"

//Computes the k-th-derivation between n values of an array
//returns a SolDerivation struct
//remember deleting it!
//
//input arrays need to be equaly spaced.
//always returns a k-4-dim array
//1st and 2nd Order accurracy: h^4
//3rd and 4th Order accurracy: h^2
SolDerivation derivArr(int derivOrder, myDouble x[], myDouble y[], int numOfPoints, myDouble stepSize) {
	if (numOfPoints < 5) {
		std::cerr << "derivArr: Array dimension does not match!" << std::endl;
		std::cin.get();
		exit(2);
	}
	if (derivOrder < 1 || derivOrder>4) {
		std::cerr << "Given order of derivation not implemented!\nreturn value=0\n";
		std::cin.get();
		exit(3);
	}

	myDouble* xRetArr = new myDouble[numOfPoints - 4];
	myDouble* yRetArr = new myDouble[numOfPoints - 4];
	switch (derivOrder)
	{
	case 1:
		for (int i = 2; i < numOfPoints - 2; i++)
		{
			xRetArr[i-2] = x[i];
			yRetArr[i-2] = 1 / (12 * stepSize) *(-y[i + 2] + 8 * y[i + 1] - 8 * y[i - 1] + y[i - 2]);
		}
		break;
	case 2:
		for (int i = 2; i < numOfPoints - 2; i++)
		{
			xRetArr[i - 2] = x[i];
			yRetArr[i - 2] = 1 / (12*stepSize * stepSize) *(-y[i + 2] + 16 * y[i + 1] - 30 * y[i] + 16 * y[i - 1] - y[i - 2]);
		}
		break;
	case 3:
		for (int i = 2; i < numOfPoints - 2; i++)
		{
			xRetArr[i - 2] = x[i];
			yRetArr[i - 2] = 1 / (2 * pow(stepSize, 3)) *(y[i + 2] - 2 * y[i + 1] + 2 * y[i - 1] - y[i - 2]);
		}
		break;
	case 4:
		for (int i = 2; i < numOfPoints - 2; i++)
		{
			xRetArr[i - 2] = x[i];
			yRetArr[i - 2] = 1 / (pow(stepSize, 4)) *(y[i + 2] - 4 * y[i + 1] + 6 * y[i] - 4 * y[i - 1] + y[i - 2]);
		}
		break;
	}

	SolDerivation retSol;
	retSol.xDeriv = xRetArr;
	retSol.yDeriv = yRetArr;
	retSol.dim = numOfPoints - 4;
	return retSol;
}

//returns the absolute maximum of a given array
// always returns a max>=0
myDouble maxArr(myDouble arr[], int dim) {
	myDouble retMax = 0;
	for (int i = 0; i < dim; i++)
	{
		if (retMax < abs(arr[i])) {
			retMax = abs(arr[i]);
		}
	}
	return retMax;
}

//calculates the maximum of the n-th Derivation of given functionpoints
//only implemented for numbers from 1 to 4
//on error returns 0
myDouble maxDeriv(int derivOrder, myDouble x[], myDouble y[], int dim, myDouble stepSize) {
	SolDerivation deriv;
	switch (derivOrder) {
	case 1:
		deriv = derivArr(1, x, y, dim, stepSize);
		break;
	case 2:
		deriv = derivArr(2, x, y, dim, stepSize);
		break;
	case 3:
		deriv = derivArr(3, x, y, dim, stepSize);
		break;
	case 4:
		deriv = derivArr(4, x, y, dim, stepSize);
		break;
	default: std::cerr << "maxDeriv: Given order of derivation not implemented!\nreturn value=0\n";
		std::cin.get();
		return 0;
	}

	myDouble retMax = maxArr(deriv.yDeriv, deriv.dim);
	delete[] deriv.xDeriv;
	delete[] deriv.yDeriv;
	return retMax;
}





//Some Testcode:
/*SolDerivation solDeriv1 = derivArr(1, InpIn.getDataX(), InpIn.getDataY(), InpIn.getNumDataPoints(), InpIn.getStepSize());
	coutArr(solDeriv1.xDeriv, solDeriv1.yDeriv, solDeriv1.dim);
	SolDerivation solDeriv2= derivArr(4, InpIn.getDataX(), InpIn.getDataY(), InpIn.getNumDataPoints(), InpIn.getStepSize());
	coutArr(solDeriv2.xDeriv, solDeriv2.yDeriv, solDeriv2.dim);*/
#include "Integration1D.hpp"


//---------------------CONSTRUCTORS-------------------------------------------------------------------------------------

//constructs an Integrand1D with given IntervalPoints
Integrand1D::Integrand1D(int numDataPoints, myDouble begin, myDouble end, f_myDouble const f) :
	numDataPoints(numDataPoints), begin(begin), end(end), f(f) {
	if (numDataPoints == 0 || begin == end || f == nullptr) {
		std::cerr << "Integrand_Interval_Constructor: wrong parameters!\n";
		std::cin.get();
		exit(2);
	}
	stepSize = (end - begin) / (numDataPoints - 1);
	dataX = fillArr([](myDouble x) {return x; }, begin, numDataPoints, stepSize);
	dataY = fillArr(f, begin, numDataPoints, stepSize);
}

//constructs an Integrand1D with given stepSize and beginValue
Integrand1D::Integrand1D(int numDataPoints, myDouble begin, f_myDouble const f, myDouble stepSize) :
	numDataPoints(numDataPoints), begin(begin), stepSize(stepSize), f(f) {
	if (numDataPoints == 0 || stepSize == 0 || f == nullptr) {
		std::cerr << "Integrand_Begin/Stepsize_Constructor: wrong parameters!\n";
		std::cin.get();
		exit(3);
	}
	end = begin + (static_cast<myDouble>(numDataPoints) - 1) * stepSize;
	dataX = fillArr([](myDouble x) {return x; }, begin, numDataPoints, stepSize);
	dataY = fillArr(f, begin, numDataPoints, stepSize);
}
//Copy Constructor
Integrand1D::Integrand1D(Integrand1D const &Int) {
	numDataPoints = Int.numDataPoints;
	stepSize = Int.stepSize;
	begin = Int.begin;
	end = Int.end;
	myDouble *datX = new myDouble[Int.numDataPoints];
	myDouble *datY = new myDouble[Int.numDataPoints];
	for (int i = 0; i < Int.numDataPoints; i++)
	{
		datX[i] = Int.dataX[i];
		datY[i] = Int.dataY[i];
	}
	dataX = datX;
	dataY = datY;
	f = Int.f;
}

//Destructor
Integrand1D::~Integrand1D() {
	delete[] dataX;
	delete[] dataY;
}


//--------Getters and Setters--------------------------------------
int Integrand1D::getNumDataPoints() {
	return numDataPoints;
}
myDouble Integrand1D::getBegin() {
	return begin;
}
myDouble Integrand1D::getEnd() {
	return end;
}
myDouble Integrand1D::getStepSize() {
	return stepSize;
}
myDouble* Integrand1D::getDataX() {
	return dataX;
}
myDouble* Integrand1D::getDataY() {
	return dataY;
}
f_myDouble  Integrand1D::getFunc() {
	return f;
}
//plots the entries of Integrand1D to console
void Integrand1D::coutData() {
	std::cout << "Integrand entries:\n";
	std::cout << "number of datapoints: " << getNumDataPoints() << "\n";
	std::cout << "stepsize:" << getStepSize() << "\n";
	std::cout << "begin: " << getBegin() << "\n";
	std::cout << "end: " << getEnd() << "\n\n";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------OTHER FUNCTIONS------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////

myDouble* fillArr(f_myDouble const &f, myDouble start, int numberPoints, myDouble stepsize) {
	myDouble* retArray = new myDouble[numberPoints];
	for (int i = 0; i < numberPoints; i++)
	{
		retArray[i] = f(start + i * stepsize);
	}
	return retArray;
}

//Integration Method with Newton Cotes
//takes an struct Integrand
//   the dimension of the data-Arrays has to be 2n+1, for n � N
//returns a solutionIntegration
SolutionIntegration newtonCotes2(Integrand1D val) {
	SolutionIntegration retSol;
	if ((val.getNumDataPoints() % 2 - 1) != 0 || val.getNumDataPoints() < 3) {
		std::cerr << "newtonCotes: given array with wrong dimension!" << std::endl;
		std::cin.get();
		exit(1);
	}

	//integration
	for (int i = 0; i <= (val.getNumDataPoints() - 3); i += 2)
	{
		retSol.solution += val.getStepSize() / 3 * (val.getDataY()[i] + 4 * val.getDataY()[i + 1] + val.getDataY()[i + 2]);
		//std::cout << "Newton Cotes: i is " << i << " solutionStep:" << retSol.solution << std::endl;
	}

	//error
	retSol.error = -(val.getEnd() - val.getBegin()) / 90 * pow(val.getStepSize(), 4)
		*maxDeriv(4, val.getDataX(), val.getDataY(), val.getNumDataPoints(), val.getStepSize());

	return retSol;
}

// Integration with trapezoidal Rule
SolutionIntegration trapezoidalRule(Integrand1D val) {
	SolutionIntegration retSol;
	if (val.getNumDataPoints() < 2) {
		std::cerr << "trapezoidal: given array with wrong dimension!" << std::endl;
		std::cin.get();
		exit(1);
	}

	//integration
	for (int i = 0; i <= (val.getNumDataPoints() - 2); i++)
	{
		retSol.solution += val.getStepSize() / 2 * (val.getDataY()[i] + val.getDataY()[i + 1]);
		//std::cout << "Trapezoidal: i is " << i << " solutionStep:" << retSol.solution << std::endl;
	}

	//error
	retSol.error = -(val.getEnd() - val.getBegin()) / 12 * pow(val.getStepSize(), 2)
		*maxDeriv(2, val.getDataX(), val.getDataY(), val.getNumDataPoints(), val.getStepSize());

	return retSol;
}

//Integration with simpsons 3/8
SolutionIntegration simpsons3_8(Integrand1D val) {
	SolutionIntegration retSol;
	if ((val.getNumDataPoints() % 3 - 1) != 0 || val.getNumDataPoints() < 3) {
		std::cerr << "Simpsons3_8: given array with wrong dimension!" << std::endl;
		std::cin.get();
		exit(1);
	}

	//integration
	for (int i = 0; i <= (val.getNumDataPoints() - 4); i += 3)
	{
		retSol.solution += 3 * val.getStepSize() / 8
			* (val.getDataY()[i] + 3 * val.getDataY()[i + 1] + 3 * val.getDataY()[i + 2] + val.getDataY()[i + 3]);
		//std::cout << "Simpsons3_8: i is " << i << " solutionStep:" << retSol.solution << std::endl;
	}

	//error
	retSol.error = -(val.getEnd() - val.getBegin()) / 80 * pow(val.getStepSize(), 4)
		*maxDeriv(4, val.getDataX(), val.getDataY(), val.getNumDataPoints(), val.getStepSize());

	return retSol;
}

//Integration with euler-maclaurin
//No Error-Guess.
SolutionIntegration eulerMaclaurin(Integrand1D val) {
	SolDerivation df2 = derivArr(2, val.getDataX(), val.getDataY(), val.getNumDataPoints(), val.getStepSize());
	myDouble df2_a = df2.yDeriv[0];
	myDouble df2_b = df2.yDeriv[df2.dim - 1];
	delete[] df2.xDeriv;
	delete[] df2.yDeriv;
	SolDerivation df3 = derivArr(3, val.getDataX(), val.getDataY(), val.getNumDataPoints(), val.getStepSize());
	myDouble df3_a = df3.yDeriv[0];
	myDouble df3_b = df3.yDeriv[df3.dim - 1];
	delete[] df3.xDeriv;
	delete[] df3.yDeriv;

	SolutionIntegration retSol;
	retSol.solution = trapezoidalRule(val).solution;
	retSol.solution -= pow(val.getStepSize(), 2) / 12 * (df2_b - df2_a);
	retSol.solution += pow(val.getStepSize(), 4) / 720 * (df3_b - df3_a);

	return retSol;
}

//Integration with Gauss-Legendre 2
//no Error-Guess
SolutionIntegration gaussLegendre2(Integrand1D val) {
	SolutionIntegration retSol;
	myDouble const const1 = (val.getEnd() - val.getBegin()) / 2;
	myDouble const const2 = (val.getEnd() + val.getBegin()) / 2;

	myDouble const x1 = -1 / sqrt(3);
	myDouble const x2 = 1 / sqrt(3);

	retSol.solution = const1 * (val.getFunc()(const1 * x1 + const2) + val.getFunc()(const1 * x2 + const2));
	return retSol;
}

//Integration with Gauss-Legendre 4
//no Error-Guess
SolutionIntegration gaussLegendre4(Integrand1D val) {
	SolutionIntegration retSol;
	myDouble const const1 = (val.getEnd() - val.getBegin()) / 2;
	myDouble const const2 = (val.getEnd() + val.getBegin()) / 2;

	//it's easier to read the code with constants,
	//they were evaluated by the compiler and don't need computation-load while runtime 
	myDouble const x1 = -sqrt(3.0 / 7.0 + 2.0 / 7.0*sqrt(6.0 / 5.0)); //=0.861...
	myDouble const x2 = -x1;
	myDouble const x3 = sqrt(3.0 / 7.0 - 2.0 / 7.0*sqrt(6.0 / 5.0));//=0.339...
	myDouble const x4 = -x3;

	myDouble const w1 = (18.0 - sqrt(30)) / 36.0;//=0.347...
	myDouble const w2 = (18.0 + sqrt(30)) / 36.0;//=0.652...


	retSol.solution = const1 * (w1*(val.getFunc()(const1 * x1 + const2) + val.getFunc()(const1 * x2 + const2))
		+ w2 * (val.getFunc()(const1 * x3 + const2) + val.getFunc()(const1 * x4 + const2)));
	return retSol;
}

//Integration with Gauss-Legendre 8
//no Error-Guess
SolutionIntegration gaussLegendre8(Integrand1D val) {
	SolutionIntegration retSol;
	myDouble const const1 = (val.getEnd() - val.getBegin()) / 2;
	myDouble const const2 = (val.getEnd() + val.getBegin()) / 2;

	//it's easier to read the code with constants,
	//they were evaluated by the compiler and don't need computation-load while runtime 
	myDouble const x[8] = {
		-0.9602898564975362,
		-0.7966664774136267,
		-0.5255324099163290,
		-0.1834346424956498,
		0.1834346424956498,
		0.5255324099163290,
		0.7966664774136267,
		0.9602898564975362,
	};
	myDouble const w[8] = {
		0.1012285362903764,
		0.2223810344533745,
		0.3137066458778874,
		0.3626837833783619,
		0.3626837833783619,
		0.3137066458778874,
		0.2223810344533745,
		0.1012285362903764,
	};

	for (int i = 0; i < 8; i++)
	{
		retSol.solution += w[i] * val.getFunc()(const1*x[i] + const2);
	}
	retSol.solution *= const1;
	return retSol;
}


//Integration Method with Splines
//takes an Integrand
//returns a solutionIntegration
//No Error Guess
SolutionIntegration splinesInteg(Integrand1D val) {

	int const n = val.getNumDataPoints();
	double* h = new double[n - 1];
	for (int i = 0; i < n - 1; i++)
	{
		h[i] = val.getDataX()[i + 1] - val.getDataX()[i];
	}
	//std::cout << "The stepsizes h are:\n";
	//coutArr(h, n - 1);

	//crate TridiagMatrix
	DynamicMatrix<myDouble> matTriDiag(n - 2, n - 2);
	for (int i = 0; i < n - 2; i++)//i step rows
	{
		for (int j = 0; j < n - 2; j++)//j step columns
		{
			//upper main diagonal
			if (i + 1 == j) {
				matTriDiag(i, j) = h[j];
			}
			//main diagonal
			if (i == j) {
				matTriDiag(i, j) = 2 * (h[i] + h[j]);
			}
			//under main diagonal
			if (i - 1 == j) {
				matTriDiag(i, j) = h[i];
			}
		}
	}
	//std::cout << "The tridiagonal matrix is:\n";
	//matTriDiag.plotMatrix();
	DynamicMatrix<myDouble> Y(n - 2, 1);
	for (int i = 1; i < n - 1; i++)
	{//formaula is for a y_n+1 so we shift the index by 1
		Y(i - 1, 0) = 6 * ((val.getDataY()[i + 1] - val.getDataY()[i]) / h[i] - (val.getDataY()[i] - val.getDataY()[i - 1]) / h[i - 1]);
	}
	/*std::cout << "Y -vec:\n";
	Y.plotMatrix();
	std::cout << "---------------------------------";*/
	ref(matTriDiag, Y);
	DynamicMatrix<myDouble> S_temp = solve(matTriDiag, Y);
	DynamicMatrix<myDouble> S(n, 1);
	S(0, 0) = 0;
	S(n - 1, 0) = 0;
	for (int i = 1; i < n - 1; i++)
	{
		S(i, 0) = S_temp(i - 1, 0);
	}
	/*std::cout << "The Solution S_temp is:\n";
	S_temp.plotMatrix();
	std::cout << "The Solution S is:\n";
	S.plotMatrix();
	std::cout << "------------------\n";*/
	//Calculate the coefficients
	double *coeffA = new double[n - 1];
	double *coeffB = new double[n - 1];
	double *coeffC = new double[n - 1];
	double *coeffD = val.getDataY();
	for (int i = 0; i < n - 1; i++)
	{
		coeffA[i] = (S(i + 1, 0) - S(i, 0)) / (6 * h[i]);
		coeffB[i] = S(i, 0) / 2;
		coeffC[i] = (val.getDataY()[i + 1] - val.getDataY()[i]) / h[i] - h[i] * (2 * S(i, 0) + S(i + 1, 0)) / 6;
	}

	SolutionIntegration retSol;
	for (int i = 0; i < n - 1; i++)
	{
		retSol.solution +=
			pow(val.getStepSize(), 4) / 4 * coeffA[i]
			+ pow(val.getStepSize(), 3) / 3 * coeffB[i]
			+ pow(val.getStepSize(), 2) / 2 * coeffC[i]
			+ val.getStepSize()*coeffD[i];
	}
	return retSol;
}



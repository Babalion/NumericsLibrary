#include <iostream>
#include "matrices.hpp"
#include "Integration1D.hpp"
//#include "RecursionInteg.hpp"
#include "universalIntegration.hpp"

const static double pi = 3.1415;
double f(double x, double y, double z)
{
    return x * y * z;
}

double f1(double x){
    return 1;
}

int main()
{
    Integrand1D boundaries[] = {
        Integrand1D(1000, 0.0, 5.0, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(1000, 0.0, pi, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(1000, 0.0, 2 * pi, std::function<myDouble(myDouble)>{[](double x) { return 0; }})};
NdimIntegrand<myDouble, myDouble, myDouble> ndI = NdimIntegrand<myDouble, myDouble, myDouble>(
        std::function<myDouble(myDouble, myDouble, myDouble)>{f}, simpsons3_8, boundaries, 3);

    std::cout << "Integrate: " << ndI.integrate() << std::endl;

/*
    double *x=new double[3];
    x[0]=1;
    x[1]=2;
    x[2]=3;
    std::cout<<redDim(f,x,f_Integrator{simpsons3_8})<<std::endl;
*/
    return 0;
}

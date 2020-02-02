#include <iostream>
#include "Sources\matrices.hpp"
#include "Sources\Integration1D.hpp"
#include "Sources\universalIntegration.hpp"

const static double pi = 3.14159;
double f(double x, double y, double z)
{
    return x * y * z;
}

double f1(double x){
    return 1;
}

int main()
{
    Integrand1D *bound1=new Integrand1D(100,0,5,f1);
    NdimIntegrand<myDouble> ndI1=NdimIntegrand<myDouble>(f_myDouble{f1},f_Integrator{gaussLegendre8},bound1,1);
    std::cout << "Integrate1: " << ndI1.integrate() << std::endl;

    delete bound1;

    Integrand1D boundaries[] = {
        Integrand1D(1000, 0.0, 5.0, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(1000, 0.0, pi, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(1000, 0.0, 2 * pi, std::function<myDouble(myDouble)>{[](double x) { return 0; }})};
NdimIntegrand<myDouble, myDouble, myDouble> ndI = NdimIntegrand<myDouble, myDouble, myDouble>(
        std::function<myDouble(myDouble, myDouble, myDouble)>{f}, simpsons3_8, boundaries, 3);

    std::cout << "Integrate3: " << ndI.integrate() << std::endl;

/*
    double *x=new double[3];
    x[0]=1;
    x[1]=2;
    x[2]=3;
    std::cout<<redDim(f,x,f_Integrator{simpsons3_8})<<std::endl;
*/
    return 0;
}

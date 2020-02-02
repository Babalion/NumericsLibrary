#include <iostream>
#include "Sources\matrices.hpp"
#include "Sources\Integration1D.hpp"
#include "Sources\universalIntegration.hpp"

const static double pi = 3.14159;
double f(double x, double y, double z)
{
    return x * y * z;
}

double f1(double x)
{
    return 1;
}
double f2(double x, double y)
{
    return x*y;
}

int main()
{
    Integrand1D *bound1 = new Integrand1D(100, 0, 5, f1);
    Integrand1D bound2[] = {Integrand1D(100,0,5,f1),Integrand1D(100,0,5,f1)};

    NdimIntegrand<myDouble, myDouble> ndI2 = NdimIntegrand<myDouble, myDouble>(
        std::function<myDouble(myDouble, myDouble)>{f2},
        f_Integrator{gaussLegendre8}, bound2, 2);

    std::cout << "Integrate2: " << ndI2.integrate() << std::endl;

    delete bound1;

    Integrand1D boundaries[] = {
        Integrand1D(10, 0.0, 5.0, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(10, 0.0, 5.0, std::function<myDouble(myDouble)>{[](double x) { return 0; }}),
        Integrand1D(10, 0.0, 5.0, std::function<myDouble(myDouble)>{[](double x) { return 0; }})};

    NdimIntegrand<myDouble, myDouble, myDouble> ndI = NdimIntegrand<myDouble, myDouble, myDouble>(
        std::function<myDouble(myDouble, myDouble, myDouble)>{f}, gaussLegendre8, boundaries, 3);

    std::cout << "Integrate3: " << ndI.integrate() << std::endl;

    return 0;
}

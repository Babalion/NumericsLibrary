#pragma once
#include <math.h>
#include <functional>
#include "GeneralNumericalSettings.hpp"
#include "Integration1D.hpp"
/*
    This header provides a universal collection of functions
    to calculate general integrals in multi dimensions.

    Furthermore, it adds various procedures of solving one dimensional integrals.

*/
// OTHER FUNCTIONS

double redDim(const std::function<double(double)> &f, Integrand1D *nIntegrandsArr, f_Integrator integ)
{
    Integrand1D thisInt = Integrand1D(
        nIntegrandsArr->getNumDataPoints(),
        nIntegrandsArr->getBegin(),
        nIntegrandsArr->getEnd(),
        f);
    
    return integ(thisInt).solution;
}

template <typename Tfirst = double, typename... Trest>
auto redDim(const std::function<double(Tfirst first, Trest... rest)> &f, Integrand1D *nIntegrandsArr, f_Integrator integ)
{
    return redDim(std::function<double(Trest...)>{
                      [=](Trest... R) -> double { return redDim([=](double x) { return f(x, R...); }, nIntegrandsArr, integ); }},
                  nIntegrandsArr + 1, integ);
}

template <typename... Args>
auto redDim(double (*f)(Args...), Integrand1D *nIntegrandsArr, f_Integrator integ)
{
    return redDim(std::function<double(Args...)>{f}, nIntegrandsArr, integ);
}

/*
    This is a general class for integrating a n-dimensional function
*/
template <typename... Args>
class NdimIntegrand
{
private:
    //the number of dimensions to integrate over
    unsigned int dim;
    std::function<myDouble(Args...)> func;
    Integrand1D *nIntegrandsArr;
    f_Integrator integrator;

public:
    NdimIntegrand(std::function<myDouble(Args...)> func_with_n_params,
                  f_Integrator integrator,
                  Integrand1D *nIntegrandsArr,
                  unsigned int dim);
    ~NdimIntegrand();

    //--------------------------------------------------------------------------------------
    //Methods
    //--------------------------------------------------------------------------------------
    myDouble integrate();
};

template <typename... Args>
NdimIntegrand<Args...>::NdimIntegrand(std::function<myDouble(Args...)> func_with_n_params,
                                      f_Integrator integrator,
                                      Integrand1D *nIntegrandsArr,
                                      unsigned int dim) : func(func_with_n_params),
                                                          nIntegrandsArr(nIntegrandsArr),
                                                          integrator(integrator),
                                                          dim(dim) {}

template <typename... Args>
NdimIntegrand<Args...>::~NdimIntegrand() {}

//--------------------------------------------------------------------------------------
//Methods
//--------------------------------------------------------------------------------------
template <typename... Args>
myDouble NdimIntegrand<Args...>::integrate()
{
    return redDim(func, nIntegrandsArr, integrator);
}
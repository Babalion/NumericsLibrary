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


/*
    This is a general class for integrating a n-dimensional function
*/
template<typename...Args>
class NdimIntegrand
{
private:
    //the number of dimensions to integrate over
    unsigned int dim;
    std::function<myDouble(Args...)> &func;
    Integrand1D* nIntegrandsArr;
    std::function<SolutionIntegration(Integrand1D)> &integrator;

    //--------------------------------------------------------------------------------------
    //Methods
    //--------------------------------------------------------------------------------------

    //Base-Template for Endrecursion and integrating a function with one parameter
    myDouble redDim(const std::function<myDouble(myDouble)> &f,Integrand1D *integrands){
        Integrand1D *integ=new Integrand1D(integrands[1].getNumDataPoints(),integrands[1].getBegin(),integrands[1].getEnd(),f);
        myDouble retVal=integrator(integ).solution;
        delete integ;
        return retVal;
    }

    // Recursion
    template<typename Tfirst, typename... Trest>
    auto redDim(std::function<myDouble(Tfirst first,Trest... rest)> &f,Integrand1D *integrands){
        return redDim(
            std::function<myDouble(Trest...)>{
                [=](Trest... R){
                    return redDim(
                        std::function<myDouble(myDouble)>{
                            [=](myDouble x){return f(x,R...);}
                        },
                        integrands[1]
                    );
                }
            },
            integrands[2]
        );
    }

    template<class...Args>
    auto redDim(myDouble(*f)(Args...),Integrand1D *integrands) {
        return redDim( std::function<myDouble(Args...)>{ f },integrands);
    }

public:
    NdimIntegrand(std::function<myDouble(Args...)> &func_with_n_params,std::function<SolutionIntegration(Integrand1D)> *integrator,Integrand1D* nIntegrandsArr,unsigned int dim);
    ~NdimIntegrand();

    //--------------------------------------------------------------------------------------
    //Methods
    //--------------------------------------------------------------------------------------
    myDouble integrate();
    

};

template<typename...Args>
NdimIntegrand<Args...>::NdimIntegrand(std::function<myDouble(Args...)> &func_with_n_params,std::function<SolutionIntegration(Integrand1D)> *integrator,Integrand1D* nIntegrandsArr,unsigned int dim)
    :func_with_n_params(func_with_n_params),nIntegrandsArr(nIntegrandsArr),integrator(integrator),dim(dim){}

template<typename...Args>
NdimIntegrand<Args...>::~NdimIntegrand(){}

template<typename...Args>
myDouble NdimIntegrand<Args...>::integrate(){
    

    return 0;
}
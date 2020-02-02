#include "universalIntegration.hpp"
//--------------------------------------------------------------------------------------------------------------------------
// GENERAL FUNCTIONS
//--------------------------------------------------------------------------------------------------------------------------

double redDim(const std::function<double(double)> f, Integrand1D nIntegrandsArr[], f_Integrator integ)
{
    Integrand1D thisInt = Integrand1D(
        nIntegrandsArr[0].getNumDataPoints(),
        nIntegrandsArr[0].getBegin(),
        nIntegrandsArr[0].getEnd(),
        f);
    
    return integ(thisInt).solution;
}
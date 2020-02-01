#include <iostream>
#include "matrices.hpp"
#include "Integration1D.hpp"
#include "universalIntegration.hpp"

const static double pi=3.1415;
const static myDouble f(myDouble x,myDouble y,myDouble z){
    return x*y*z;
}

int main(){
    Integrand1D boundaries[]={
        Integrand1D(1000,0.0,5.0   ,std::function<myDouble(myDouble)>{[](double x){return 0;}}),
        Integrand1D(1000,0.0,pi    ,std::function<myDouble(myDouble)>{[](double x){return 0;}}),
        Integrand1D(1000,0.0,2*pi  ,std::function<myDouble(myDouble)>{[](double x){return 0;}})};
    NdimIntegrand<myDouble,myDouble,myDouble> ndI= NdimIntegrand<myDouble,myDouble,myDouble>(
        std::function<myDouble(myDouble,myDouble,myDouble)>{f},simpsons3_8,boundaries,3);

    return 0;
}
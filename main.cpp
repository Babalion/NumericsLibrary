/*
    #include "hartree.cpp"



    //Wave functions of H-Atom
    double u100(Vec3Dsp* vec){
        return 1/sqrt(4*pi)*2/sqrt(pow(a0,3))*exp(-vec->r/a0); //ABWANDLUNG mit Z!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    double u200(Vec3Dsp* vec){
        return 1/sqrt(4*pi)*1/sqrt(2*pow(a0,3))*(1-vec->r/2/a0)*exp(-vec->r/2/a0); //ABWANDLUNG mit Z!!!!!!!!!!!!!!!!!!!!!!!!!
    }


    int main(){
        //1. startfunctions
        const int nOfParticles=2;
        f3_double* startfunc =new f3_double[nOfParticles];
        startfunc[0]=u100;
        startfunc[1]=u200;

        //2. Calculate V_i
        auto* V=new f3_double[nOfParticles];

        for (size_t i = 0; i < nOfParticles; i++){
            V[i]=calculateVi_r(startfunc,i,nOfParticles);
        }
        



        return 0;
    }
*/

#include <iostream>
#include "matrices.hpp"
#include "universalIntegration.hpp"

const static double pi=3.1415;
myDouble f(myDouble x,myDouble y,myDouble z){
    return x*y*z;
}

int main(){
    Integrand1D boundaries[]={Integrand1D(1000,0,5,nullptr),Integrand1D(1000,0,pi,nullptr),Integrand1D(1000,0,2*pi,nullptr)};
    NdimIntegrand<myDouble,myDouble,myDouble>(std::function<myDouble(myDouble,myDouble,myDouble)>{f},simpsons3_8,boundaries,3);

    return 0;
}
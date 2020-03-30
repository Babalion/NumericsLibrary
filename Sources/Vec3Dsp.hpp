#pragma once
#include <math.h>
#include "GeneralNumericalSettings.hpp"

class Vec3Dsp{
private:
    myDouble r;
    myDouble th;
    myDouble phi;
    myDouble x;
    myDouble y;
    myDouble z;
public:
    Vec3Dsp(myDouble,myDouble,myDouble);
    ~Vec3Dsp();

//getter and setter
myDouble getR();
myDouble getThetha();
myDouble getPhi();
myDouble getX();
myDouble getY();
myDouble getZ();
void setR(myDouble);
void setThetha(myDouble);
void setPhi(myDouble);
void setX(myDouble);
void setY(myDouble);
void setZ(myDouble);

//methods

    myDouble calcDistance(Vec3Dsp*);
};
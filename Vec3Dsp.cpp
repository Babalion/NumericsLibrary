#include "Vec3Dsp.hpp"

Vec3Dsp::Vec3Dsp(double r,double th,double phi):r(r),th(th),phi(phi)
{
    x=r*sin(th)*cos(phi);
    y=r*sin(th)*sin(phi);
    z=r*cos(th);
}

Vec3Dsp::~Vec3Dsp(){}



//................................................
//.......GETTER AND SETTER........................
//................................................
myDouble Vec3Dsp::getR(){
    return r;
}
myDouble Vec3Dsp::getThetha(){
    return th;
}
myDouble Vec3Dsp::getPhi(){
    return phi;
}
myDouble Vec3Dsp::getX(){
    return x;
}
myDouble Vec3Dsp::getY(){
    return y;
}
myDouble Vec3Dsp::getZ(){
    return z;
}  
void Vec3Dsp::setR(myDouble _r){
    r=_r;
    x=r*sin(th)*cos(phi);
    y=r*sin(th)*sin(phi);
    z=r*cos(th);
}
void Vec3Dsp::setThetha(myDouble _th){
    th=_th;
    x=r*sin(th)*cos(phi);
    y=r*sin(th)*sin(phi);
    z=r*cos(th);
}
void Vec3Dsp::setPhi(myDouble _phi){
    phi=_phi;
    x=r*sin(th)*cos(phi);
    y=r*sin(th)*sin(phi);
    z=r*cos(th);
}
void Vec3Dsp::setX(myDouble _x){
    x=_x;
    r=sqrt(x*x+y*y+z*z);
    th=acos(z/r);
    phi=atan2(y,x);
}
void Vec3Dsp::setY(myDouble _y){
    y=_y;
    r=sqrt(x*x+y*y+z*z);
    th=acos(z/r);
    phi=atan2(y,x);
}
void Vec3Dsp::setZ(myDouble _z){
    z=_z;
    r=sqrt(x*x+y*y+z*z);
    th=acos(z/r);
    phi=atan2(y,x);
}


//................................................
//.......METHODS..................................
//................................................

//calculates the distance between another spherical vector
double Vec3Dsp::calcDistance(Vec3Dsp other){
    return sqrt(pow(x-other.x,2)+pow(y-other.y,2)+pow(z-other.z,2));
}
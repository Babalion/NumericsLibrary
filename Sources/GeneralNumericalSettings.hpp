#pragma once

#include <functional>

// this type is going to be used in any numerical calculation
// you can change it to long double, if you need more precision. 
typedef double myDouble;

// a simple real-function from R->R
typedef std::function<myDouble(myDouble)> f_myDouble;
typedef std::function<myDouble(myDouble,myDouble,myDouble)> f3_myDouble;
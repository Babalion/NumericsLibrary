#pragma once
#include <math.h>
#include <functional>
#include "Integration1D.hpp"


double redDim(const std::function<double(double)> &f, double *a,f_Integrator integ){
    return (f(0)+f(*a)) * *a;
}

template <typename Tfirst = double, typename... Trest>
auto redDim(const std::function<double(Tfirst first, Trest... rest)> &f, double *a,f_Integrator integ){
    return redDim(std::function<double(Trest...)>{
                      [=](Trest... R) -> double { return redDim([=](double x) { return f(x, R...); }, a,integ); }},
                  a + 1,
                  integ);
}

template <typename... Args>
auto redDim(double (*f)(Args...), double *a,f_Integrator integ){
    return redDim(std::function<double(Args...)>{f}, a,integ);
}
#ifndef _INTEGRATE_H
#define _INTEGRATE_H

namespace integrate {

// Sane C++ solution for arbitrary functions
using integrand_t = std::function<double(double)>;
// ...but e.g. GSL doesn't care, so we unfortunately need this.
using integrand_fptr_t = double (*)(double);

/* Integrate func using the respective method over the inclusive range [begin,
 * end] on meshsize number of points.
 *
 * A meshsize of 0 returns 0.0. The meshsize requested may not be the exact
 * meshsize used, depending on the method.
 *
 * func is expected to take a single argument that is a double and return a
 * double */
template<class F> double simpson(double begin, double end, int meshsize, F func);
template<class F> double   milne(double begin, double end, int meshsize, F func);
double legendre(double begin, double end, int meshsize, integrand_fptr_t func);

} // end namespace integrate

// This must be set to allow arbitrary template instantiation.
#ifdef HEADER_INLINE_TEMPLATES
    #include "integrate.cpp"
#endif

#endif // _INTEGRATE_H defined

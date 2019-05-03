#include <stdexcept>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include "integrate.h"

namespace integrate {

/* The use of OpenMP in simpson and milne does not seem to produce any speedup
 * on my 4-core machine; however, I only ever see 100% CPU usage, so there is
 * possibly something going on.  */


// NOTE: meshsize-1 is the number of intervals corresponding to a given meshsize

/* Calculate the composite Simpson's rule for func(x) between x=begin and x=end on at least
 * meashsize points.
 *
 * Quadrature weights: step_size/3*(1, 4, 1)
 *
 * meshsize-1 is rounded up to the nearest multiple of two. A meshsize < 0 throws an
 * std::domain_error, and meshsize == 0 is guaranteed to return 0.0.
 */
template<class F> double simpson(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;

    // Fix meshsize
    if ((meshsize-1) % 2 != 0)
        meshsize += 2 - (meshsize-1)%2;

    double step = (end-begin)/(meshsize-1);

    // First point gets first weight = 1
    double integral = func(begin);
    #ifdef OMP
    #pragma omp parallel for reduction(+:integral)
    #endif
    for (int i = 1; i < meshsize-1; ++i) {
        const double x = begin + i*step;
        // Summing over multiple intervals; ends overlap, giving double weight (2*1 = 2)
        integral += (i % 2 == 0 ? 2.0 : 4.0)*func(x);
    }
    // Last point gets last weight = 1
    integral += func(end);
    
    // Remaining factors out front
    return step/3.0*integral;
}

/* Calculate the composite Milne's rule for func(x) between x=begin and x=end on at least
 * meshsize points.
 *
 * Quadrature weights: step_size/45*(14, 64, 24, 64, 14)
 *
 * meshsize-1 is rounded up to the nearest multiple of 4. A meshsize < 0 throws an
 * std::domain_error, and meshsize == 0 is guaranteed to return 0.0.
 */
template<class F> double milne(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;

    // Fix meshsize
    if ((meshsize-1) % 4 != 0)
        meshsize += 4 - (meshsize-1) % 4;

    const double step = (end - begin)/(meshsize-1);

    // First point gets first weight
    double integral = 14*func(begin);
    double mid_integral = 0.0;
    #ifdef OMP
    #pragma omp parallel for reduction(+:mid_integral)
    #endif
    for (int i = 1; i < meshsize-1; ++i) {
        const double x = begin + i*step;
        int weight;
        // Summing over multiple intervals; ends overlap, giving double weight (2*14)
        switch (i % 4) {
            case 0: weight = 2*14; break;
            case 1: weight = 64;  break;
            case 2: weight = 24;  break;
            case 3: weight = 64;  break;
        }
        mid_integral += weight*func(x);
    }
    // Last point gets last weight
    integral += mid_integral + 14*func(end);

    // Remaining factors out front
    return step*integral/45.0;
}

/* Interface with GSL fixed Legendre method. Calculate integral of func(x) between x=begin and
 * x=end on meshisze points. 
 *
 * A meshsize < 0 throws an std::domain_error, and meshsize == 0 is guaranteed to return 0.0.
 * If a GSL error occurs, prints to stderr and return 0.0.
 */
double legendre(double begin, double end, int meshsize, integrand_fptr_t func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;

    gsl_function gfunc;
    // This is hacky... but it should work. Note that func actually only takes one argument...
    gfunc.function = (double (*)(double, void *)) func;
    gfunc.params = nullptr;

    auto workspace = gsl_integration_fixed_alloc(
        gsl_integration_fixed_legendre, meshsize, begin, end, 0.0, 0.0
    );

    double ret;
    // This performs the integration, putting the result in ret.
    int err = gsl_integration_fixed(&gfunc, &ret, workspace);
    gsl_integration_fixed_free(workspace);
    if (err) {
        std::cerr << __FILE__ << ':' << __LINE__ << ": WARNING: GSL error code " << err
                  << ". Returning 0.0." << std::endl;
    }

    return ret;
}

// If we don't allow arbitrary template instantiation, then at least compile these.
#ifndef HEADER_INLINE_TEMPLATES
    template double simpson<integrand_t>(double, double, int, integrand_t);
    template double simpson<integrand_fptr_t>(double, double, int, integrand_fptr_t);
    template double milne<integrand_t>(double, double, int, integrand_t);
    template double milne<integrand_fptr_t>(double, double, int, integrand_fptr_t);
#endif

} // end namespace integrate

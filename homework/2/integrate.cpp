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


/* If meshsize is even, 1 is added to make it odd. */
template<class F> double simpson(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;
    meshsize += 1 - meshsize % 2;

    double step = (end-begin)/(meshsize-1);

    double integral = func(begin);
    #ifdef OMP
    #pragma omp parallel for reduction(+:integral)
    #endif
    for (int i = 1; i < meshsize-1; ++i) {
        const double x = begin + i*step;
        integral += (i % 2 == 0 ? 2.0 : 4.0)*func(x);
    }
    
    integral += func(end);
    
    return step/3.0*integral;
}

/* meshsize is rounded up to the next multiple of 4. */
template<class F> double milne(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;
    if (meshsize % 4 != 0)
        meshsize += 4 - meshsize % 4;

    const double step = (end - begin)/(meshsize-1);

    double integral = func(begin);
    double mid_integral = 0.0;
    #ifdef OMP
    #pragma omp parallel for reduction(+:mid_integral)
    #endif
    for (int i = 1; i < meshsize-1; ++i) {
        const double x = begin + i*step;
        int weight;
        switch (i % 4) {
            case 0: weight = 16; break;
            case 1: weight = 6;  break;
            case 2: weight = 16; break;
            case 3: weight = 7;  break;
        }
        mid_integral += weight*func(x);
    }
    integral += 2*mid_integral;
    integral += func(end);

    return 2.0/45.0*step*integral;
}

/* Interface with GSL fixed Legendre method. */
double legendre(double begin, double end, int meshsize, integrand_fptr_t func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;

    // This is hacky... but it should work.
    gsl_function gfunc;
    gfunc.function = (double (*)(double, void *)) func;
    gfunc.params = nullptr;

    auto workspace =
        gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, meshsize, begin, end,
                                    0.0, 0.0);

    double ret;
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

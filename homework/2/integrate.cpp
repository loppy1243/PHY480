#include <stdexcept>
#include <functional>
#include "integrate.h"

namespace integrate {

/* If meshsize is even, 1 is added. This ensures an even number of
 * subintervals. */
template<class F>
double simpson(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;
    meshsize += 1 - meshsize % 2;

    double step = (end-begin)/(meshsize-1);

    double integral = func(begin);
    #ifdef OMP
    #pragma omp parallel
    #endif
    for (int i = 1; i < meshsize-1; ++i) {
        const double x = begin + i*step;
        integral += (i % 2 == 0 ? 2.0 : 4.0)*func(x);
    }
    
    integral += func(end);
    
    return step/3.0*integral;
}

/* meshsize is rounded up to the next multiple of 3. This ensures a number of
 * subintervals divisible by 4. */
template<class F>
double milne(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;
    if (meshsize % 3 != 0)
        meshsize += 3 - meshsize % 3;

    // |  .  .  .  |  .  .  .  |  .  .  .  |  .  .  .  |
    //  \/
    // step
    //
    // Dots correspond to the mesh, and bars correspond to the intervals forming the
    // composite rule.
    const int n_intervals = meshsize/3;
    const double step = (end - begin)/(meshsize + n_intervals);

    // OpenMP is not working with this for some reason (in my machine with 4 cores); the
    // plotting in the OpenMP case makes it look like there is a race condition. I thought
    // perhaps accuraccy was an issue; some Googling suggested Kahan summation, but that does
    // not appear to help in the slightest.

    double integral = 0.0; 
    #ifdef OMP
    #pragma omp parallel
    #endif
    {
        double c = 0.0;
        #pragma omp for reduction(+:integral)
        for (int n = 0; n <= n_intervals; ++n) {
            const double x = begin + 4.0*n*step;
            const double y = 2.0*func(x + step) + 2.0*func(x + 3.0*step) - func(x + 2.0*step) - c;
            const double t = integral + y;
            c = (t - integral) - y;
            integral = t;

        }
    }

    return 4.0/3.0*step*integral;
}

// If we don't allow arbitrary template instantiation, then at least compile these.
#ifndef HEADER_INLINE_TEMPLATES
    template double simpson<integrand_t>(double, double, int, integrand_t);
    template double milne<integrand_t>(double, double, int, integrand_t);
#endif

} // end namespace integrate

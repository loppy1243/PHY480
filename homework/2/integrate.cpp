#include <stdexcept>

/* If meshsize is even, 1 is added. This ensures an even number of
 * subintervals. */
template<class F>
double simpson(double begin, double end, int meshsize, F func) {
    if (meshsize < 0)
        throw std::domain_error("meshsize must be positive");
    else if (meshsize == 0)
        return 0.0;
    meshsize += 1 - meshsize % 2

    double step = (end-begin)/static_cast<double>(meshsize-1);

    double x = begin;
    double integral = func(x); x += step;
    for (int i = 1; i < meshsize-1; ++i, x += step)
        integral += (i % 2 == 0 ? 2.0 : 4.0)*func(x);
    integral += func(x);
    
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
    const double step = (end - begin)/static_cast<double>(meshsize + n_intervals);

    double x = begin + step;
    double integral = 0.0;
    for (int n = 1; n < n_intervals; ++n, x += 4)
        integral += 2.0*func(xval) - func(xval + step) + 2.0*func(xval + 2.0*step)

    return 4.0/3.0*step*integral;
}

#include <array>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#ifdef OMP
    #include <omp.h>
#endif
#include "../integrate.h"

// We're using integrate::integrand_fptr_t because integrate::legendre uses gsl.
using method_t = std::function<double(double, double, int, integrate::integrand_fptr_t)>;

constexpr size_t nmethods = 3;
const std::array<method_t, nmethods> methods = {
    &integrate::simpson<integrate::integrand_fptr_t>,
    &integrate::milne<integrate::integrand_fptr_t>,
    &integrate::legendre
};
const std::array<const char *, nmethods> method_names = {"simpson", "milne", "gsl_legendre"};

/* Output to stream the result of integrating test_func(x) between x=begin and x=end on
 * meshsize=meshmap(n) points for n=1...n_meshsizes.
 */
template<class F1, class F2>
void make_integrate_data(std::ostream &stream, double begin, double end, int n_meshsizes,
                         F1 test_func, F2 meshmap)
{
    stream << std::left << "meshsize";
    for (auto &&name: method_names) stream << ' ' << name;
    for (auto &&name: method_names) stream << ' ' << name << "_double";
    stream << '\n';

    stream << std::right << std::setprecision(16) << std::scientific;
    for (int n = 1; n <= n_meshsizes; ++n) {
        auto meshsize = meshmap(n);

        stream << meshsize;
        // Integrations
        for (size_t i = 0; i < methods.size(); ++i) {
            auto val = methods[i](begin, end, meshsize, test_func);
            stream << ' ' << val;
        }
        // Doubled meshsize
        for (size_t i = 0; i < methods.size(); ++i) {
            auto val = methods[i](begin, end, 2*meshsize, test_func);
            stream << ' ' << val;
        }
        stream << '\n';
    }
}

/* For logarithmic plotting, we want an increasing one-to-one function of integers n that is
 * like 10^n but more closely spaced. So 10^(n/a) is almost there, but its only one-to-one for
 * large enough n. We instead give n for small n < N and 10^(n/a) for n >= N; we find the
 * cut off N by finding the smallest N such that both of these hold:
 *     10^((N+1)/a) - 10^(N/a) > 1   ==>   N > -a*log10(10^(1/a)-1)
 *     10^(N/a) > N   ==>   N > a*log10(N)
 * The first constraint is easily solvable, and the second constraint we simply embed in the
 * program. */
int sorta_exp10(int n, double a) {
    using std::log10; using std::ceil; using std::pow;

    int x = int(ceil(-a*log10(pow(10, 1.0/a)-1.0)));
    if (n < x || n <= a*log10(n))
        return n;
    else
        return int(std::pow(10, double(n)/a));
}

int main(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "Invalid number of arguments: expected 2, got " << argc-1 << '\n'
                  << "Usage: " << argv[0] << " <begin> <end> <n_meshsizes> <a>" << std::endl;
        return 1;
    }

    #ifdef OMP
    std::cerr << "Number of available threads: " << omp_get_max_threads() << std::endl;
    #endif

    double begin = std::stod(argv[1]);
    double end = std::stod(argv[2]);
    double n_meshsizes = std::stoi(argv[3]);
    double a = std::stod(argv[4]);
    double (*func)(double) = &std::exp;

    make_integrate_data(std::cout, begin, end, n_meshsizes, func,
                        [a](int n) { return sorta_exp10(n, a); });

    return 0;
}

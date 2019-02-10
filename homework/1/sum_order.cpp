/*******************************************************************************
* 
* Compare the accuracy of summing the series 1/n from n=1->N vs. n=N->1.
* 
* Author:  Nicholas Todoroff (todorof3@msu.edu)
* Created: 2019-02-05
*
*******************************************************************************/
/* Analysis of data:
*
*  A plot of the file `sum_order.dat` can be found in `plots/sum_order.pdf`. This data was
*  generated with the call `./build/bin/sum_order.x -n 10000000 -s 6`.
*
*  We see that the upward (1->N) and downward (N->1) sums are mostly equal until the number of
*  terms is about 2e4. The two methods keep diverging gracefully untul about 2e5 terms. We see
*  from the lower end of the bottom right plot that the "oscillations" in the relative error
*  are due to the value of the upward sum diverging from the upward sum erratically and
*  intersecting it at certain points. The upward sum then saturates at about 2e6 terms with a
*  value of about 15.58. This suggests that the upward sum is a less accurate method, which is
*  what we would expect: summing upward, we start wit a large number (1) and progressively add
*  smaller and smaller numbers; the relative difference between the sum and the next term to
*  add becomes increasingly larger, making further additions less accurate. The saturation
*  occurs when this relative difference is greater than 1 + machine epsilon.
*
*  Assuming this is the case, then with N=(number of terms) the slopes in the relative error
*  plot tell us that for 0 < N < 2e4 the relative error of the upward sum is proportional to
*  N^0.38. 
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <unistd.h>

int const ERR_INVALID_INPUT = 1;

//// Define sum_up(), sum_down() templated so that we can potentially test them with float,
//// double, and perhaps something else.

template<class T>
T sum_up(int n) {
    T tot = 1.0;
    for (int i=2; i <= n; ++i) tot += 1.0/(T) i;
    return tot;
}

template<class T>
T sum_down(int n) {
    T tot = 1.0/(T) n;
    for (int i=n-1; i >= 1; --i) tot += 1.0/(T) i;
    return tot;
}

void usage(std::ostream &stream, char const *prog_name) {
    stream << "Usage: " << prog_name << " [-n n_max] [-s scaling]" << std::endl
           << "    Defaults: n_max=1000000, scaling=5" << std::endl
           << std::endl
           << "    Sum n terms for n in the range 1 to n_max. Values of n are chosen by" << std::endl
           << "    starting with at n=1 with a step size of 1, and then scaling the step size" << std::endl
           << "    for each power of 10. E.g.," << std::endl
           << "          1 <= n < 10   => step size = 1" << std::endl
           << "         10 <= n < 100  => step size = 5 if scaling=5" << std::endl
           << "        100 <= n < 1000 => step size = 25" << std::endl;
}

int main(int argc, char **argv) {
    int optchar, n_max=1000000, scaling=5;
    // Check command line for options -n and -s, and error with a usage message if anything
    // else if found.
    while ((optchar = getopt(argc, argv, "n:s:")) != -1) {
        switch (optchar) {
            case 'n': n_max = std::stoi(optarg); break;
            case 's': scaling = std::stoi(optarg); break;
            case '?': usage(std::cerr, argv[0]); return ERR_INVALID_INPUT;
        }
    }
    if (optind < argc) {
        usage(std::cerr, argv[0]);
        return ERR_INVALID_INPUT;
    }

    int const ndigits = 1 + (int) floor(log10(n_max));
    // If ndigits < the width of the terms column-header (7), then use that.
    int const terms_col_width = ndigits < 5 ? 5 : ndigits;
    int const prec = 8;

    char const *const space = "   ";
    // Print header "terms sum_up sum_down" with appropriate spacing.
    std::cout << std::left
                 << std::setw(terms_col_width) << "terms" << space
    // 6 for remaining parts of scientific notation e.g. "1.e+12"
                 << std::setw(prec+6) << "sum_up" << space
                 << std::setw(prec+6) << "sum_down" << space
                 << std::setw(prec+6) << "rel_diff" << std::endl
    // Set format flags for the following loop.
              << std::right << std::scientific << std::setprecision(prec);
    for (int i = 0, step = 1; i < (int) log10(n_max); ++i, step *= scaling) {
        for (int n = (int) pow(10, i); n < (int) pow(10, i+1); n += step) {
            float up = sum_up<float>(n);
            float down = sum_down<float>(n);
            float rel_diff = fabs(up-down)/((fabs(up)+fabs(down))/2.0);

            std::cout << std::setw(terms_col_width) << n << space << up << space
                         << down << space << rel_diff << std::endl;
        }
    }

    return 0;
}

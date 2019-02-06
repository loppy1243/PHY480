#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

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
    stream << "Usage: " << prog_name << " <n_max>" << std::endl
           << "    n_max -- Sum n terms for each n in 1 to n_max." << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments: expected 1, got " << argc << std::endl;
        usage(std::cerr, argv[0]);
        return ERR_INVALID_INPUT;
    }

    int n_max;

    try {
        n_max = std::stoi(argv[1]);
    }
    catch (std::invalid_argument ex) {
        std::cerr << "Invalid argument: expected integer" << std::endl;
        usage(std::cerr, argv[0]);
        return ERR_INVALID_INPUT;
    }

    int const ndigits = 1 + (int) floor(log10(n_max));
    // If ndigits < the width of the terms column header (7), then use that.
    int const terms_col_width = ndigits < 5 ? 5 : ndigits;
    int const prec = 8;

    char const *const space = "   ";
    // Print header "terms sum_up sum_down" with appropriate spacing.
    std::cout << std::left
              << std::setw(terms_col_width) << "terms"
    // 6 for remaining parts of scientific notation e.g. "1.e+12"
              << space << std::setw(prec+6) << "sum_up"
              << space << std::setw(prec+6) << "sum_down"
              << space << std::setw(prec+6) << "rel_diff" << std::endl
    // Set format flags for the following loop.
              << std::right << std::scientific << std::setprecision(prec);
    for (int n=1; n <= n_max; ++n) {
        float up = sum_up<float>(n);
        float down = sum_down<float>(n);
        float rel_diff = fabs(up-down)/((fabs(up)+fabs(down))/2.0);

        std::cout << std::setw(terms_col_width) << n
                  << space << up
                  << space << down
                  << space << rel_diff << std::endl;
    }

    return 0;
}

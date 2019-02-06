#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

int const ERR_INVALID_INPUT = 1;

//// Define sum_up(), sum_down() templated so that we can potentially test them with float,
//// double, and perhaps something else.

// (reasonably) assumes that T is floating-point
template<class T>
T sum_up(int n) {
    T tot = 0;
    for (int i=1; i <= n; ++i) tot += 1.0/n;
    return tot;
}

// (reasonably) assumes that T is floating-point
template<class T>
T sum_down(int n) {
    T tot = 0;
    for (int i=n; i > 0; --i) tot += 1.0/n;
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

    int ndigits = 1 + (int) floor(log10(n_max));
    // If ndigits < the width of the terms column header (7), then use that.
    int terms_col_width = ndigits < 5 ? 5 : ndigits;

    char const *const space = "   ";
    // Print header "terms sum_up sum_down" with appropriate spacing.
    std::cout << std::left
              << std::setw(terms_col_width) << "terms"
    // 8 for precision + 6 for remaining parts of scientific notation e.g. "1.e+12"
              << space << std::setw(8+6) << "sum_up"
              << space << std::setw(8+6) << "sum_down"
              << space << std::setw(8+6) << "rel_diff" << std::endl
    // Set format flags for the following loop.
              << std::right << std::scientific << std::setprecision(8);
    for (int n=1; n <= n_max; ++n) {
        float up = sum_up<float>(n);
        float down = sum_down<float>(n);
        float rel_diff = abs(up-down)/((abs(up)+abs(down))/2.0);

        std::cout << std::setw(terms_col_width) << n
                  << space << up
                  << space << down
                  << space << rel_diff << std::endl;
    }

    return 0;
}

//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl    furnstahl.1@osu.edu
//               Nicholas Todoroff todorof3@msu.edu    (from 05-Feb-2019)
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//      05-Feb-2019  Improve formatting and remove useless comments
//                   Generate pi from cmath atan(), rename pi -> PI
//                   Define standalone circle_area() function
//                   Output to a file instead of stdout
//                   Add error handling to input
//                   Wrap into Circle class
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//*********************************************************************// 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <cmath>
using namespace std;

//*********************************************************************//

char const *const OUTPUT_FILE = "area.out";

// Error codes to return from main()
int const ERR_INVALID_INPUT = 1;
int const ERR_BAD_IO = 2;

// tan(pi/4) == 1 => atan(1) == pi/4
double const PI = 4.0*atan(1.0);

// Explicit inlining is likely redundant, but w/e.
inline double square(double x) { return x*x; }

// Represents a circle by storing the radius.
class Circle {
    double _radius;

public:
    Circle(double radius) {
        if (radius < 0.0)
            throw domain_error("Radius must be non-negative");

        this->_radius = radius;
    }

    inline double radius() { return this->_radius; }
    inline double area() { return PI*square(this->_radius); }
};

int main() {
    double radius;
   
    cout << "Enter the radius of a circle: ";
    cin >> radius;
    // If the read goes bad for some reason
    if (cin.bad()) {
        cerr << "I/O error" << endl;
        return ERR_BAD_IO;
    }
    // If the input could not be parsed as a double
    else if (cin.fail()) {
        cerr << "Invalid input: expected number!" << endl;
        return ERR_INVALID_INPUT;
    }
    else if (radius < 0.0) {
        cerr << "Radius cannot be negative!" << endl;
        return ERR_INVALID_INPUT;
    }

    Circle circle(radius);

    ofstream file(OUTPUT_FILE);
    // Default precision of 6 is too small, so we increase to 9.
    file << setprecision(9)
         << "radius = " << radius << ",  area = " << circle.area() << endl;
    file.close();
    cout << "Output written to " << OUTPUT_FILE << endl;

    return 0;
}

//*********************************************************************//

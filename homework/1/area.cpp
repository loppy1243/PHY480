//  file: area.cpp
//
//  This program calculates the area of a circle, given the radius.
//
//  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu
//
//  Revision history:
//      02-Jan-2004  original version, for 780.20 Computational Physics
//      01-Jan-2010  updates to "To do" wishlist
//      12-Jan-2016  comment out "using namespace std;"
//
//  Notes:  
//   * compile with:  "g++ -o area.x area.cpp"
//
//  To do:
//   1. output the answer with higher precision (more digits)
//   2. use a "predefined" value of pi or generate it with atan
//   3. define an inline square function
//   4. split the calculation off into a function (subroutine)
//   5. output to a file (and/or input from a file)
//   6. add checks of the input (e.g., for non-positive radii)
//   7. rewrite using a Circle class
//
//*********************************************************************// 

#include <iostream>
using namespace std;

//*********************************************************************//

const double pi = 3.1415926535897932385;

int main () {
    double radius;

    cout << "Enter the radius of a circle: ";
    cin >> radius;

    // Standard area formula
    double area = pi * radius * radius;

    cout << "radius = " << radius << ",  area = " << area << endl;

    return 0;
}

//*********************************************************************//

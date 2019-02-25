/* Integrate func using the respective method over the inclusive range [begin,
 * end] on meshsize number of points. A meshsize of 0 returns 0.0.
 *
 * func is expected to take a single argument that is a double and return a
 * double */
template<class F>
double simpson(double begin, double end, int meshsize, F func);
template<class F>
double milne(double begin, double end, int meshsize, F func);

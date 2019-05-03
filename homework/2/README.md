# Building
Run `make` to build `integrate.o`

Run `make test` to build the test program into `./bin/integrate_test.x`.

Run `make plots` to make the plots in `integrate_test_plt.pdf`, as long as
`integrate_test.dat` exists.

The provided `integrate_test.dat` was generated with
```
./integrate_test.x 0 10 60 15 >integrate_test.dat
```
This integrate from 0 to 10 on 60 meshpoints with a "stride" of 15. The "stride" is the
parameter `a` in the function `sorta_exp10` in the source `test/integrate_test.cpp`.

# Analysis
We see quite clearly in `integrate_test_plt.pdf` contains three plots. The first is the result
of each integration method vs. the number of meshpoints it was calculated on. The second is
the relative error of each method with the `gsl_legendre` method. The third is the relative
error of each method with itself evaluated at twice the number of meshpoints.

We see from the second plot that Simpson's rule goes like `n^-3.999 ~ (1/h)^-3.999`, which is
well within error for the expected power of `-4`. Similarly, Milne's rule goes like `n^-5.66`,
and is within error for the expected power of `-5`.

The third plot forgoes the comparison with the more accurate `gsl_legendre` method, and
instead is a self-relative error between the value at the given number of meshpoints and the
value at twice that. We still see the same results: Simpson's goes like `n^-3.984` and Milne's
like `n^-5.71`, and to boot we have about the same standard error in the fit.

The optimum number of points for Milne integration will be when the relative error is
approximately machine epsilon (`~10^-16` for double-precision floats), and we would expect
this to be on the order of `10^(-16/-5) ~ 1500` meshpoints. We see visually that this
emperically happens around `1000` meshpoints, so our estimate wasn't so bad. In fact, if we
take machine epsilon to be `10^-15`, then this is very good. We get the same results looking
at the self-relative error.

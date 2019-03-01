## This is not quite finished

# Analysis
We see quite clearly in `integrate_test_plt.pdf`, assuming the GSL Legendre integration
is most accurate out of the three methods, that the relative error in Milne rule goes like
```
    rel.err. ~ n^-1.035 ~ (1/h)^-1.035
```
for `n` evalutation points and a step size of `h`.

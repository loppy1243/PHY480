set terminal pdfcairo noenhanced
set output "derivative_test_plt.pdf"

datafile = 'derivative_test.dat'

f(x) = a*x + b
fit [-1:1.4] f(x) datafile using 1:5 via a,b

sigfigs(x, err) = (x < 0 ? 1 : 2) + ceil(abs(log10(abs(x))-log10(abs(err))))
title_format(a, a_err, b, b_err) = \
    '(%.'.sigfigs(a, a_err).'g +- %.2g)*log(h) + (%.'.sigfigs(b, b_err).'g +- %.2g)'
title_string(a, a_err, b, b_err) = sprintf(title_format(a, a_err, b, b_err), a, a_err, b, b_err)

set title '2nd Extrapolated Derivative Relative Error'
set xlabel 'log10(h)'
set ylabel 'log10(rel. err.)'
set key top left
plot datafile using 1:5 title columnhead(5), \
     f(x)               title title_string(a, a_err, b, b_err)

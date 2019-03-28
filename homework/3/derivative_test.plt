set terminal pdfcairo noenhanced
set output "derivative_test_plt.pdf"

datafile = 'derivative_test.dat'

f(x) = a*x + b
fit [-1:1.4] f(x) datafile using 1:5 via a,b

set title '2nd Extrapolated Derivative Rel. Err.'
set xlabel 'log10(h)'
set ylabel 'log10(rel. err.)'
set key top left
plot datafile using 1:5 title columnhead(5), \
     f(x)               title sprintf('%g*log(h) + %g', a, b)

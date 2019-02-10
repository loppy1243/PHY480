if (!exists('datafile')) {
    datafile = 'bessel.dat'
}
if (!exists('plotfile')) {
    plotfile = 'bessel.pdf'
}

set terminal pdfcairo size 8,9 noenhanced font 'Times,20'
set output plotfile
set timestamp

# Setup to use filled circles in as labels for dots
set style line 1 linetype 1 pointtype 7 pointsize 1
set style line 2 linetype 2 pointtype 7 pointsize 1
set style line 3 linetype 3 pointtype 7 pointsize 1

f(a, b, x) = a*x + b
g(a, b, x) = 10.0**(f(a, b, log10(x)))
fit [2:10]  f(a1, b1, log10(x)) datafile using 1:(log10($5)) via a1,b1
fit [30:40] f(a2, b2, log10(x)) datafile using 1:(log10($5)) via a2,b2
fit [30:40] f(a3, b3, log10(x)) datafile using 1:(log10($6)) via a3,b3
fit [2:10]  f(a4, b4, log10(x)) datafile using 1:(log10($7)) via a4,b4
array a[4]; array b[4]
a[1] = a1; a[2] = a2; a[3] = a3; a[4] = a4
b[1] = b1; b[2] = b2; b[3] = b3; b[4] = b4

array fit_titles[4]
do for [i=1:4] {
    fit_titles[i] = sprintf('%g*x + %g', a[i], b[i])
}

array titles[3];
titles[1] = 'Up and Down Recursion'
titles[2] = 'Down Recursion and GSL'
titles[3] = 'Up Recursion and GSL'

set key top left
set multiplot layout 3,1
set logscale
set ytics format '%.0e'
set yrange [1e-17:1]

set title 'Bessel Function Methods: Relative Differences vs. x-Values'
plot 1/0 linestyle 1 with points title titles[1], \
     datafile using 1:5 linestyle 1 with dots notitle, \
     g(a[1], b[1], x) linewidth 3 title fit_titles[1], \
     g(a[2], b[2], x) linewidth 3 title fit_titles[2]

unset title
plot 1/0 linestyle 2 with points title titles[2], \
     datafile using 1:6 linestyle 2 with dots notitle, \
     g(a[3], b[3], x) linewidth 3 title fit_titles[3]

plot 1/0 linestyle 3 with points title titles[3], \
     datafile using 1:7 linestyle 3 with dots notitle, \
     g(a[4], b[4], x) linewidth 3 title fit_titles[4]

if (!exists('datafile')) {
    datafile = 'sum_order.dat'
}
if (!exists('plotfile')) {
    plotfile = 'sum_order.pdf'
}

default_font = 'Times'
default_font_size = '14'
default_font_str = default_font.','.default_font_size

set terminal pdfcairo noenhanced size 6,6 font default_font_str
set output plotfile
set timestamp

# Setup to use filled circles in as labels for dots
set style line 1 linetype 1 pointtype 7 pointsize 1
set style line 2 linetype 2 pointtype 7 pointsize 1
set style line 3 linetype 3 pointtype 7 pointsize 1

array titles[3];
titles[1] = 'Upward'; titles[2] = 'Downward'; titles[3] = 'Rel. Diff'

f(a, b, x) = a*x + b
fit [:4] f(a1, b1, x) datafile using (log10($1)):(log10($4)) via a1,b1
fit [4:] f(a2, b2, x) datafile using (log10($1)):(log10($4)) via a2,b2

set key top left
set logscale
set multiplot

set lmargin at screen 0.15
set rmargin at screen 0.9
set tmargin at screen 0.9
set bmargin at screen 0.5625
set yrange [1e-8:]
set title 'Upward vs. Downward Summation of 1/n'
set xlabel 'Terms'
set ylabel 'Relative Difference'
set format '%.0e'
# This first line gives visible labels for the dots as larger filled circles.
plot 1/0 linestyle 1 with points title titles[3], \
     datafile using 1:4 linestyle 1 notitle with dots, \
     10**f(a1, b1, log10(x)) title sprintf('%f*x + %f', a1, b1), \
     10**f(a2, b2, log10(x)) title sprintf('%f*x + %f', a2, b2)

set lmargin at screen 0.15
set rmargin at screen 0.50
set tmargin at screen 0.4375
set bmargin at screen 0.1
unset yrange
set title 'Upward and Downward Summation'
set xlabel 'Terms'
set ylabel 'Sum'
unset logscale y
set xtics font default_font.',10'
set ytics format '%g'
# This first line gives visible labels for the dots as larger filled circles.
plot for [i=2:3] 1/0 linestyle i with points title titles[i-1], \
     datafile using 1:2 linestyle 2 notitle with dots, \
     ''       using 1:3 linestyle 3 notitle with dots

set lmargin at screen 0.55
set rmargin at screen 0.9
set tmargin at screen 0.4375
set bmargin at screen 0.1
set xrange [5e5:]
set title '(near significant divergence)'
set xlabel 'Terms'
unset ylabel
set xtics font default_font_str
replot

if (!exists('datafile')) {
    datafile = 'sum_order.dat'
}
if (!exists('plotfile')) {
    plotfile = 'sum_order.pdf'
}

set terminal pdfcairo noenhanced size 6,6
set output plotfile

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

set lmargin at screen 0.1
set rmargin at screen 0.9
set tmargin at screen 0.9
set bmargin at screen 0.55
set title 'Upward vs. Downward Summation of 1/n'
set ylabel 'Relative Difference'
plot 1/0 linestyle 1 with points title titles[3], \
     datafile using 1:4 linestyle 1 notitle with dots, \
     10**f(a1, b1, log10(x)) title sprintf('%f*x + %f', a1, b1), \
     10**f(a2, b2, log10(x)) title sprintf('%f*x + %f', a2, b2)

set lmargin at screen 0.1
set rmargin at screen 0.9
set tmargin at screen 0.45
set bmargin at screen 0.1
set title 'Upward and Downward Summation'
set xlabel 'Terms'
set ylabel 'Upward Sum'
set y2label 'Downward Sum'
set ytics nomirror
set y2tics auto
unset logscale y
unset logscale y2
plot for [i=2:3] 1/0 linestyle i with points title titles[i-1], \
     datafile using 1:2 linestyle 2 notitle axes x1y1 with dots, \
     ''       using 1:3 linestyle 3 notitle axes x1y2 with dots

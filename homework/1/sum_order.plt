if (!exists('datafile')) {
    datafile = 'sum_order.dat'
}
if (!exists('plotfile')) {
    plotfile = 'sum_order.pdf'
}

set terminal pdfcairo noenhanced
set output plotfile

set logscale y
set xlabel 'Terms'
set ylabel 'Up/Down-sum Relative Difference'
plot datafile using 1:4 title columnheader(4)

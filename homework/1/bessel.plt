if (!exists('datafile')) {
    datafile = 'bessel.dat'
}
if (!exists('plotfile')) {
    plotfile = 'bessel.pdf'
}

set terminal pdfcairo
set output plotfile

set multiplot layout 2,1
plot datafile using 1:4 title columnheader(4)
set logscale
replot

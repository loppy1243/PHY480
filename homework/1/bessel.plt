if (!exists('datafile')) {
    datafile = 'bessel.dat'
}
if (!exists('plotfile')) {
    plotfile = 'bessel.pdf'
}

set terminal pdfcairo size 16,9 noenhanced font 'Times,20'
set output plotfile

array titles[3];
titles[1] = 'Up and Down Recursion'
titles[2] = 'Down Recursion and GSL'
titles[3] = 'Up Recursion and GSL'

set key top left
set multiplot layout 3,1
set logscale
do for [i=5:7] {
    unset title
    if (i == 5) {
        set title 'Relative Differences vs. x-Values (log-log)'
    }
    plot datafile using 1:i linetype i-4 title titles[i-4]
}

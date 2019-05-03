datafile = 'eigen_basis.dat'
plotfile = 'eigen_basis_plt.pdf'

set terminal pdfcairo noenhanced size 4,4
set output plotfile

stats datafile using 1 nooutput

set multiplot layout 2,1
set title 'Exact Coloumb Wavefunction vs. Truncated HO Basis'
do for [n=0:1] {
    if (n == 1) {
        set xlabel 'Radius'
    }
    plot datafile index 4*n   using 1:2 with lines dashtype '-' title columnhead(2), \
         datafile index 4*n   using 1:3 with lines              title columnhead(3), \
         datafile index 4*n+1 using 1:3 with lines              title columnhead(3), \
         datafile index 4*n+2 using 1:3 with lines              title columnhead(3), \
         datafile index 4*n+3 using 1:3 with lines              title columnhead(3)
    unset title
}

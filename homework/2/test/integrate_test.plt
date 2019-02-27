if (!exists('datafile')) {
    datafile = 'integrate_test.dat'
}
!mkdir -p plots

font_str = 'Times'
small_font_size = 10
small_font = font_str.','.small_font_size
normal_font_size = 12
normal_font = font_str.','.normal_font_size
title_font_size = 14
title_font = font_str.','.title_font_size
set terminal pdfcairo size 4,4 font normal_font
set output 'integrate_test_plt.pdf' 

stats datafile using 2:3 nooutput
ncolumns = STATS_columns

do for [i=2:ncolumns] {
    set style line i-1 linetype i-1
    set style line ncolumns+i-1 linetype i-1 linewidth 3
}

reldiff(x, y) = 2.0*(abs(x-y))/(abs(x) + abs(y))

f(x) = a*x + b
g(x) = 10**(f(log10(x)))
fit [20:] f(log10(x)) datafile using 1:(log10(reldiff($2, $3))) via a,b

set multiplot
set logscale

pad_left   = 0.15
pad_right  = 0.05
pad_middle = 0.2
pad_top    = 0.1
pad_bottom = 0.1
set lmargin at screen 0.0+pad_left
set rmargin at screen 1.0-pad_right
set bmargin at screen 0.5+pad_middle/2.0
set tmargin at screen 1.0-pad_top
set title 'Integral of exp(x) from x=0 to 1 vs. Mesh Size' font title_font
set xlabel 'Mesh Size'
set ylabel 'Value'
set ytics font small_font
plot for [i=2:ncolumns] datafile using 1:i with dots linestyle i-1 notitle, \
     for [i=2:ncolumns] 1/0 with circles fill solid linestyle ncolumns+i-1 title columnhead(i)
set ytics font normal_font

set lmargin at screen 0.0+pad_left
set rmargin at screen 1.0-pad_right
set bmargin at screen 0.0+pad_bottom
set tmargin at screen 0.5-pad_middle/2.0
set title 'Method Value Relative Differences' font title_font
set xlabel 'Mesh Size'
set ylabel 'Value'

sigfigs(x, err) = 1 + ceil(abs(log10(abs(x))-log10(abs(err))))
a_sigfigs = sigfigs(a, a_err)
b_sigfigs = sigfigs(b, b_err)
title_format = '(%.'.a_sigfigs.'g +- %.2g)*x + (%.'.b_sigfigs.'g +- %.2g)'
plot for [i=2:ncolumns] for [j=i+1:ncolumns] datafile \
         using 1:(reldiff(column(i), column(j))) linestyle i-1 notitle, \
     for [i=2:ncolumns] for [j=i+1:ncolumns] 1/0 \
         with circles fill solid linestyle ncolumns+i-1 \
         title columnhead(i).' vs.  '.columnhead(j), \
     g(x) title sprintf(title_format, a, a_err, b, b_err)

unset multiplot

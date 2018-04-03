datafile='./hist.dat'
plotfile='./hist_rand.png'

set output plotfile
set term png

set title "Distribution of Random Numbers [0-100]"
set xlabel "Bins"
set ylabel "Number of Arguments"

set style data histogram
set boxwidth 0.9  relative
set style fill solid 1.0

set offset 0, 0, 2, 0
set yrange [0:]
set xrange [0:]

set key autotitle columnheader
plot datafile using 1:2 with boxes fillcolor 'cyan'

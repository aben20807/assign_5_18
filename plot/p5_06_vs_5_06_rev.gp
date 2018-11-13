reset
set ylabel 'cycle'
set xlabel 'degree'
set xtics 1000
set xtics rotate by -60
set format x "%.0t*10^%T";
set format y "%.0t*10^%T";
set style fill solid
set key center top
set title 'poly test'
set term png enhanced font 'Verdana,18' size 1600, 1200
set output '5_6_vs_5_6_rev.png'

plot [:10000][0:] \
'output.txt' using 1:2 with points pointtype 7 title '5.6', \
'' using 1:3 with points pointtype 7 title '5.6_rev', \

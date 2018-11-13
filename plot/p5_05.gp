reset
set ylabel 'cycle'
set xlabel 'degree'
set ytics 500
set xtics 100
set xtics rotate by -60
set format x "%.0t*10^%T";
set format y "%.1t*10^%T";
set style fill solid
set key center top
set title 'poly test'
set term png enhanced font 'Verdana,18' size 1600, 1200
set output 'assign_5_5_and_5_6.png'

plot [:1000][0:] \
'output.txt' using 1:2 with points pointtype 7 title '5.5', \
'' using 1:3 with points pointtype 7 title '5.6', \

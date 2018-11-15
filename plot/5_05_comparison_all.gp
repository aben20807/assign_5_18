reset
set ylabel 'cycle'
set xlabel 'degree'
set ytics 200
set xtics 100
set xtics rotate by -60
set format x "%.0t*10^%T";
set format y "%.1t*10^%T";
set style fill solid
set key center top
set title 'poly test'
set term png enhanced font 'Verdana,18' size 1600, 1200
set output '5_05_comparison_all.png'

set grid ytics lt 1 lw 2 lc rgb "#bbbbbb"
set grid xtics lt 1 lw 2 lc rgb "#bbbbbb"
show grid
    
plot [:1000][0:] \
'output.txt' using 1:2 with line lw 2 title '5.5', \
'' using 1:3 with line lw 2 title '5.5rev2', \
'' using 1:4 with line lw 2 title '5.5rev3', \
'' using 1:5 with line lw 2 title '5.5rev4', \
'' using 1:6 with line lw 2 title '5.5rev5', \
'' using 1:7 with line lw 2 title '5.5rev6', \
'' using 1:8 with line lw 2 title '5.5rev7', \
'' using 1:9 with line lw 2 title '5.5rev8', \
'' using 1:10 with line lw 2 title '5.5-3way', \
'' using 1:11 with line lw 2 title '5.5-6way', \
'' using 1:12 with line lw 2 title '5.5-9way', \

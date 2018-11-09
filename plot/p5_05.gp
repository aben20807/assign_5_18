reset
set ylabel 'cycle'
set xtics 100000
set xtics rotate by -60
set style fill solid
set key center top
set title 'poly test'
set term png enhanced font 'Verdana,10'
set output 'assign_5_5_and_5_6.png'

plot [:1000000][0:] \
'output.txt' using 1:2 with dots title '5.5', \
'' using 1:3 with dots title '5.6', \

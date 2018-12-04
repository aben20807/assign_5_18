#include "gen_plot.h"

void gen_plot(int n, char *argv[])
{
    FILE *pf = fopen("dynamic_gen/plot.gp", "w");
    fprintf(pf, "reset\n");
    fprintf(pf, "set ylabel 'cycle'\n");
    fprintf(pf, "set xlabel 'degree'\n");

    fprintf(pf, "set ytics 500\n");
    fprintf(pf, "set xtics 100\n");
    fprintf(pf, "set xtics rotate by -60\n");

    fprintf(pf, "set format x \"%%.0t*10^%%T\";\n");
    fprintf(pf, "set format y \"%%.1t*10^%%T\";\n");

    fprintf(pf, "set style fill solid\n");
    fprintf(pf, "set key center top\n");

    fprintf(pf, "set title 'poly test'\n");
    fprintf(pf, "set term png enhanced font 'Verdana,18' size 1600, 1200\n");
    fprintf(pf, "set output 'poly.png'\n\n");

    fprintf(pf, "set grid ytics lt 1 lw 2 lc rgb \"#bbbbbb\"\n");
    fprintf(pf, "set grid xtics lt 1 lw 2 lc rgb \"#bbbbbb\"\n\n");

    fprintf(pf, "plot [:1000][0:] \\\n");

    for (int i = 0; i < n; i++) {
        fprintf(pf, "'output.txt' using 1:%d with line lw 2 title '%s', \\\n",
                i + 2, argv[i + 2]);
    }

    // fprintf(pf, "'' using 1:3 with line lw 2 title '5.5', \\ ");

    fclose(pf);
}
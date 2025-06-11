#include <stdio.h>
#include <stdlib.h>

#define X_MAX 100
#define Y_MAX 100
#define N 1000		// number of agents
#define K 100		// number of iteration

struct Population {
    double type[N];
    double x[N];
    double y[N];
};

struct Population pop;

void initPop() {
    unsigned int i = 0;
    while (i < N) {
        pop.type[i] = rand() % 2;	// either 0 (if rand return is even), or 1 (otherwise)
        pop.x[i] = rand() % X_MAX + 1;
        pop.y[i] = rand() % Y_MAX + 1;
        i++;
    }

    return;
}

void updatePlot(FILE *gp) {

    unsigned int i = 0;
    while (i < N) {
        fprintf(gp, "replot\n");
        fprintf(gp, "%g %g %g\n", pop.x[i], pop.y[i], pop.type[i]);
        i++;
    }

    return;
}

int main() {

    initPop(pop);

    FILE *gnuplot = popen("gnuplot", "w");

    // setup gnuplot
    fprintf(gnuplot,"set palette model RGB defined ( 0 'blue', 1 'red' )\n"	// set color palette
                    "set pointsize 2\n"						// set point size
                    "plot '-' using 1:2:3 palette\n");    			// use inline data (http://gnuplot.info/docs_5.5/loc3515.html)
    updatePlot(gnuplot);
    // useful commands before closing (http://gnuplot.info/docs_5.5/loc7936.html)
    fprintf(gnuplot, "bind all 'alt-End' 'exit gnuplot'\n"
                     "pause mouse close\n"
                     "e\n");
    fflush(gnuplot);

    for (;;);

    pclose(gnuplot);

    return 0;
}

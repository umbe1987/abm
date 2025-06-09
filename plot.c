#include <stdio.h>
#include <stdlib.h>

#define X_MAX 100
#define Y_MAX 100
#define N 100		// number of agents

struct Population {
    double type[N];
    double x[N];
    double y[N];
};

void initPop(struct Population *p) {
    unsigned char i = 0;
    while (i < N) {
        p->type[i] = rand() % 2;	// either 0 (if rand return is even), or 1 (otherwise)
        p->x[i] = rand() % X_MAX + 1;
        p->y[i] = rand() % Y_MAX + 1;
        i++;
    }
}

int main() {

    struct Population pop;
    initPop(&pop);

    FILE *gnuplot = popen("gnuplot", "w");

    // setup gnuplot
    fprintf(gnuplot,"set palette model RGB defined ( 0 'blue', 1 'red' )\n"	// set color palette
                    "set pointsize 2\n"						// set point size
                    "plot '-' using 1:2:3 palette\n");				// use inline data (http://gnuplot.info/docs_5.5/loc3515.html)

    unsigned char i = 0;
    while (i < N) {
        fprintf(gnuplot, "%g %g %g\n", pop.x[i], pop.y[i], pop.type[i]);
        i++;
    }
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);

    for (;;)

    pclose(gnuplot);

    return 0;
}

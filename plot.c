#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define X_MAX 100
#define Y_MAX 100
#define N 1000		// number of agents
#define K 1000		// number of iteration

struct Agent {
    unsigned int type;
    unsigned int x;
    unsigned int y;
};

struct Agent pop[N];

void initPop() {
    for (unsigned int i = 0; i < N; i++) {
        pop[i].type = rand() % 2;	// either 0 (if rand return is even), or 1 (otherwise)
    }

    return;
}

void updatePop() {
    for (unsigned int i = 0; i < N; i++) {
        pop[i].x = rand() % X_MAX + 1;
        pop[i].y = rand() % Y_MAX + 1;
    }
}

void updatePlot(FILE *gp, unsigned int iter) {
    FILE *data = fopen("data", "w+");
    for (unsigned int i = 0; i < N; i++) {
        fprintf(data, "%d %d %d\n", pop[i].x, pop[i].y, pop[i].type);
    }
    fclose(data);

    fprintf(gp,"set title \"%d\"\n", iter);
    if (iter == 0) {
        fprintf(gp, "plot 'data' using 1:2:3 palette\n");
    } else {
        fprintf(gp, "replot\n");
    }
    fflush(gp);

    return;
}

int main() {

    initPop(pop);
    FILE *gp = popen("gnuplot -persist", "w");

    // setup gnuplot
    fprintf(gp,"set palette model RGB defined ( 0 'blue', 1 'red' )\n"	// set color palette
               "set pointsize 2\n"					// set point size
               "set xrange[0:%d]\n"
               "set yrange[0:%d]\n", X_MAX, Y_MAX);
    for (unsigned int i = 0; i < K; i++) {
        updatePop();
        updatePlot(gp, i);
        usleep(25000);
    }
    pclose(gp);

    return 0;
}

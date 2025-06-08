#include <stdio.h>
#include <stdlib.h>

#define X_MAX 100
#define Y_MAX 100
#define N 100		// number of agents

struct Agent {
    unsigned char type;
    double x;
    double y;
};

void initAgent(struct Agent *agent) {
    agent->type = rand() % 2;		// either 0 (if rand return is even), or 1 (otherwise)
    agent->x = rand() % X_MAX + 1;
    agent->y = rand() % Y_MAX + 1;
};

int main() {

    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "plot '-'\n");
    unsigned char i = 0;
    while (i < N) {
        struct Agent a;
        initAgent(&a);
        fprintf(gnuplot, "%g %g\n", a.x, a.y);
        i++;
    };
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);

    for (;;);

    pclose(gnuplot);

    return 0;
}

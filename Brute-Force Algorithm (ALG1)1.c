#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

typedef struct {
    int x;
    int y;
} Point;

double distance(Point p1, Point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

void findClosestPair(Point points[], int n, int *p1, int *p2) {
    double minDist = INFINITY;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                *p1 = i;
                *p2 = j;
            }
        }
    }
}

int main() {
    int n_values[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int m = 10;

    for (int k = 0; k < sizeof(n_values) / sizeof(n_values[0]); k++) {
        int n = n_values[k];
        double avg_rt = 0.0;

        for (int i = 0; i < m; i++) {
            Point *points = (Point *)malloc(n * sizeof(Point));
            for (int j = 0; j < n; j++) {
                points[j].x = rand() % RAND_MAX;
                points[j].y = rand() % RAND_MAX;
            }

            struct timeval start, end;
            int p1, p2;

            gettimeofday(&start, NULL);
            findClosestPair(points, n, &p1, &p2);
            gettimeofday(&end, NULL);

            double rt = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            avg_rt += rt;

            free(points);
        }

        avg_rt /= m;

        printf("n = %d\n", n);
        printf("Average Running Time (Brute-Force): %lf seconds\n", avg_rt);
        printf("-----------------------------------------------\n");
    }

    return 0;
}

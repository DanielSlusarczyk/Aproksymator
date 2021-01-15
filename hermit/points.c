#include "points.h"
#include <stdlib.h>
#include <stdio.h>
static int
realloc_pts_failed (points_t * pts, int size)
{
  return realloc (pts->x, size * sizeof *pts->x) == NULL
    || realloc (pts->y, size * sizeof *pts->y) == NULL;
}

int read_pts_failed(FILE* inf, points_t* pts) {
	int amount;
	//The amount of points
	double x, y;
	//x, y co-ordinates
	int tmp = 0;

	if (fscanf(inf, "%d", &amount) != 1) {
		return 1;
	}
	//The first number must determine the amount of points

	pts->x = (double*)malloc(amount * sizeof(double));
	if (pts->x == NULL) {
		return 1;
	}
	pts->y = (double*)malloc(amount * sizeof(double));
	if (pts->y == NULL) {
		free(pts->x);
		return 1;
	}

	//Reading points...
	while (fscanf(inf, "%lf %lf", &x, &y) == 2) {
		pts->x[tmp] = x;
		pts->y[tmp] = y;
		pts->n++;
		tmp++;
		if (tmp > amount) {
			printf("Zadeklarowano mniej punktow!\n");
			return 1;
		}
	}
	if (tmp != amount) {
		printf("Zadeklarowano: %d, wczytano: %d\n", amount, tmp);
	}

	return 0;


}

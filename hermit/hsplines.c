#include "hsplines.h"

#include <stdlib.h>

#define MALLOC_FAILED( P, SIZE ) (((P)=malloc( (SIZE)*sizeof( *(P))))==NULL)

int
alloc_spl(spline_t* spl, int n)
{
	spl->nb = n;
	//n=nb
	spl->a = (double**)calloc(n, sizeof(double*));
	spl->x = (int*)calloc(2, sizeof(double));
	if (spl->a == NULL || spl->x == NULL)
		return 1;
	return 0;
}

int
read_spl(FILE* inf, spline_t* spl)
{
	int i;
	if (fscanf(inf, "%d", &(spl->nb)) != 1 || spl->nb < 0)
		return 1;

	if (alloc_spl(spl, spl->nb))
		return 1;

	for (i = 0; i < spl->nb; i++) {
		spl->a[i] = (double*)malloc(sizeof(double));
		if (fscanf(inf, "%lf", spl->a[i]) != 1)
			return 1;
	}

	return 0;
}

void
write_spl(spline_t* spl, FILE* ouf)
{
	int i;
	fprintf(ouf, "%d\n", spl->nb);
	for (i = 0; i < spl->nb; i++)
		fprintf(ouf, "%g\n", spl->a[i][0]);
}

double
value_spl(spline_t* spl, double x)
{
	double sum = 0;
	int i;
	for (int i = 0; i < spl->nb; i++) {
		if (i == 0)
			sum += spl->a[0][0];
		else if (i == 1)
			sum += (spl->a[1][0]) * (2 * x);
		else if (i == 2)
			sum += (spl->a[2][0]) * (4 * x * x - 2);
		else if (i == 3)
			sum += (spl->a[3][0]) * (8 * x * x * x - 12 * x);
		else if (i == 4)
			sum += (spl->a[4][0]) * (16 * x * x * x * x - 48 * x * x + 12);
		else if (i == 5)
			sum += (spl->a[5][0]) * (32 * x * x * x * x * x - 160 * x * x * x + 120 * x);
		else if (i == 6)
			sum += (spl->a[6][0]) * (64 * x * x * x * x * x * x * x - 480 * x * x * x * x + 720 * x * x - 120);
	}
	return sum;
}

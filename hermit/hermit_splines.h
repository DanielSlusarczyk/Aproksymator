#ifndef HERMIT_SPLINES_H
#define HERMIT_SPLINES_H

typedef struct {
	int n;
	//The amount of coefficients in polynomial
	double* a;
	//Cofficients
	int* x;
	//Powers of x
}spline_t;

int alloc_spl(spline_t* spl, int n);
//Allocates memory

void write_spl(spline_t* spl, FILE* ouf);
//Writes a polynomial to a file

int read_spl(FILE* inf, spline_t* spl);
//Reads a polynomial from a file

#endif

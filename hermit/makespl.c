#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "backsubst.h"
#include "mat_io.h"
#include "gauss.h"

#include "makespl.h"
#include "hsplines.h"
#include "points.h"


typedef struct {
	int n, m;
	//Dimensions of matrix
	double** v;
	//Values of elements 
} mat_t;

double value_pol(double x, int h);
//Calculates the value of h-degree Hermit's polynomials for x
//Otherwise returns NAN

mat_t* makes_matrix(int n, int m);
//Allocates a matrix- size: n x m
//Otherwise returns NULL

mat_t* complete_matrix(mat_t* M, double va, int n, int m);
//Completes matrix with values

void print2screen(mat_t* M);
//Prints matrix to screen

mat_t* inverse_multiplication(mat_t* A, mat_t* R);
//Muliplies matrix by transposed matrix, returns result

mat_t* multiplication(mat_t* A, mat_t* B, mat_t* R);
//Multiplies matrix by second matrix

mat_t* free_me(mat_t* X);
//Frees up space

void make_spl(points_t* pts, spline_t* spl) {

	

	//double nb= pts->n-3 >10 ? 10: pts->n-3;
	int nb = 6;
	//Nb- the accuracy of the approximation 2<n<7
	//char* nbEnv = getenv("APPROX_BASE_SIZE");

	//if (nbEnv != NULL && atoi(nbEnv) > 0)
	//	nb = atoi(nbEnv);

	mat_t* D = makes_matrix(pts->n, nb);
	mat_t* A = makes_matrix(nb, 1);
	mat_t* f = makes_matrix(pts->n, 1);
	mat_t* DTD = makes_matrix(nb, nb);
	mat_t* DTf = makes_matrix(nb, 1);
	if (D == NULL || A == NULL || f == NULL||DTD==NULL||DTf==NULL) {
		free_me(D);
		free_me(A);
		free_me(f);
		free_me(DTD);
		free_me(DTf);
		spl = NULL;
		return;
	}
	
	printf("Zaalokowana pamiec:\n");
	printf("Macierz D:\n");
	print2screen(D);
	printf("Macierz f:\n");
	print2screen(f);
	printf("Macierz A:\n");
	print2screen(A);
	printf("Macierz DTD:\n");
	print2screen(DTD);
	printf("Macierz DTf:\n");
	print2screen(DTf);


	//Values of Matrix D:
	int temp = 0;
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < pts->n; j++) {
			D = complete_matrix(D, value_pol(pts->x[j], temp), j, i);
		}
		temp++;
	}

	//Values of Matrix f and A:
	for (int i = 0; i < pts->n; i++) {
		f = complete_matrix(f, pts->y[i], i, 0);
	}
	printf("Po wypelnieniu wartosciami:\n");
	printf("Macierz A:\n");
	print2screen(D);
	printf("Macierz f:\n");
	print2screen(f);
	printf("Macierz A:\n");
	print2screen(A);

	DTD = inverse_multiplication(D, DTD);
	DTf = multiplication(D, f, DTf);

	printf("Po skwadratowieniu macierzy:\n");
	print2screen(DTD);
	print2screen(DTf);

	//Calculating...
	Matrix* An= readFromCall(DTD->n, DTD->m, DTD->v);
	Matrix* bn= readFromCall(DTf->n, DTf->m, DTf->v);
	Matrix* x= createMatrix(bn->r, 1);
	Matrix r;
	int res=eliminate(An,bn);
	if(res==1){
		printf("Wczytana macierz jest osobliwa\n");
		freeMatrix(An);
		freeMatrix(bn);
		spl=NULL;
		return;
	}
	if(x!=NULL){
		res=backsubst(x, An, bn);
		printf("\nMacierz rozwiazan:\n\n");
		printToScreen(x);

	}
	else{
		fprintf(stderr, "Nie udalo sie utworzyc wektora wynikowego x\n");
		return;
	}

	alloc_spl(spl, nb);

	printf ("tu jestem\n");
	//Writing...
	spl->x[0]=pts->x[0];
	spl->x[1]=pts->x[pts->n-1];
	spl->n=2;
	printf ("Tu\n");
	for (int i=0; i<nb; i++){
		spl->a[i]=x->data[i];
	}
printf("Tu jestem\n");	


	free_me(D);
	free_me(A);
	free_me(f);
	//free_me(DTD);
	//free_me(DTf);

	return;
}

double value_pol(double x, int h) {
	if (h == 0) {
		return 1;
	}
	else if (h == 1) {
		return 2*x;
	}
	else if (h == 2) {
		return 4 * x * x - 2;
	}
	else if (h == 3) {
		return 8 * x * x * x - 12 * x;
	}
	else if (h == 4) {
		return 16 * x * x * x * x - 48*x * x + 12;
	}
	else if (h == 5) {
		return 32 * x * x * x * x * x - 160 * x * x * x + 120 * x;
	}
	else if (h == 6) {
		return 64 * x * x * x * x * x * x * x - 480 * x * x * x * x * x + 720 * x * x  - 120;
	}
	else {
		return NAN;
	}

}

mat_t* makes_matrix(int n, int m) {
	mat_t* tmp = (mat_t*)malloc(sizeof(mat_t));
	if (tmp == NULL) {
		return NULL;
	}
	tmp->m = m;
	tmp->n = n;
	tmp->v = (double**)malloc(n * sizeof(double*));
	if (tmp->v == NULL) {
		return NULL;
	}
	for (int i = 0; i < tmp->n; i++) {
		tmp->v[i] = (double*)calloc(n, sizeof(double));
		if (tmp->v[i] == NULL) {
			return NULL;
		}
	}
	return tmp;
}

mat_t* complete_matrix(mat_t* M, double va, int n, int m) {
	M->v[n][m] = va;
	return M;
}

void print2screen(mat_t* M) {
	for (int i = 0; i < M->n; i++) {
		printf("[ ");
		for (int j = 0; j < M->m; j++) {
			printf("%15.4lf ", M->v[i][j]);
		}
		printf("]\n");
	}
}

mat_t* inverse_multiplication(mat_t* A, mat_t *R) {
	double sum=0;
	for (int i = 0; i < A->m; i++) {
		for (int j = 0; j < A->m; j++) {
			for (int k = 0; k < A->n; k++) {
				sum += A->v[k][i] * A->v[k][j];
			}
			R->v[i][j] = sum;
			sum = 0;
		}
	}
	return R;
}

mat_t* multiplication(mat_t* A, mat_t* B, mat_t* R) {
	double sum = 0;
	for (int i = 0; i < A->m; i++) {
		for (int j = 0; j < B->n; j++) {
			for (int k = 0; k < B->n; k++) {
				sum += A->v[k][i] * B->v[k][j];
			}
			R->v[i][j] = sum;
			sum = 0;
		}
	}
	return R;
}

mat_t* free_me(mat_t* X) {
	for (int i = 0; i < X->n; i++) {
		free(X->v[i]);
	}
	free(X->v);
	free(X);
	return NULL;
}

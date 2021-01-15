#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


void compare_solutions(Matrix* x, Matrix* r);

int main(int argc, char** argv) {
	int t= TEST > 0 ? 1 : 0;
	int res;
	Matrix* A = readFromFile(argv[1]);
	Matrix* b = readFromFile(argv[2]);
	Matrix* x;
	Matrix* r;
	if(t==1){
		r = readFromFile(argv[3]);
	}

	if (A == NULL) return -1;
	if (b == NULL) return -2;

	printf("\nWczytany uklad rownan: \n");
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A, b);
	if (res==1){
	printf("Wczytana macierz jest osobliwa\n");
	freeMatrix(A);
	freeMatrix(b);
	exit (1); 
	}
	x = createMatrix(b->r, 1);

	if (x != NULL) {
		res = backsubst(x, A, b);
		printf("\nMacierz rozwiazan: \n\n");
		printToScreen(x);
		if(t==1)
			compare_solutions(x,r);
		freeMatrix(x);
		if(t==1)
		freeMatrix(r);
	}

	else {
		fprintf(stderr, "Nie udalo sie utworzyć wektora wynikowego x.\n");
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
void compare_solutions(Matrix* x, Matrix* r){	
	int i;
	int j=0;
	for (i=0; i<x->r; i++){
		if((x->data[i][0] - r->data[i][0])>=1e-8 ||-(x->data[i][0] - r->data[i][0])>=1e-12){
			printf("NIE ZGADZA SIE WIERSZ %d!\n",i+1);
			printf("Poprawna liczba to %10.10f zamiast %10.10f \n", r->data[i][0], x->data[i][0]);
			j=1;
		}
	}	
	if(j!=1)
		printf("WSZYSTKO SIE ZGADZA \n");
}

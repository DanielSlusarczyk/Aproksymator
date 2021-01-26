#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Zwraca <> NULL - udalo sie wczytac
 * Zwraca == NULL - podczas wczytywania wystapil blad
 */
Matrix* readFromCall(int n, int m, double** dane) {
	int ir, ik;
	Matrix* mat = createMatrix(n, m);
	if (mat != NULL) {
		for (ir = 0; ir < n; ir++) {
			for (ik = 0; ik < m; ik++) {
				mat->data[ir][ik] = dane[ir][ik];
			}
		}
	}
	else {
		fprintf(stderr, "Gauss: wystąpił problem podczas tworzenia macierzy do obliczen o rozmiarach %d x %d", n, m);
	}
	return mat;

}
Matrix* readFromFile(char* fname) {
	int r, c;
	int ir, ic;
	FILE* fin = fopen(fname, "r");
	Matrix* mat = NULL;

	if (fin != NULL) {
		if (fscanf(fin, "%d %d", &r, &c) != 2) {
			printf("\nBlad wczytywania macierzy\n\n");
			return NULL;
		}
		mat = createMatrix(r, c);
		if (mat != NULL) {
			for (ir = 0; ir < r; ir++) {
				for (ic = 0; ic < c; ic++) {
					if (fscanf(fin, "%lf", &(mat->data[ir][ic])) != 1) {
						printf("\nBlad wczytywania macierzy\n\n");
						return NULL;
					}
				}
			}
		}
		else {
			fprintf(stderr, "Wystąpił problem podczas tworzenia macierzy o rozmiarach %d x %d dla danych z pliku: %s\n", r, c, fname);
		}

		fclose(fin);
	}
	else {
		fprintf(stderr, "Nie mogę otworzyć pliku o nazwie: %s\n", fname);
	}

	return mat;
}

void printToScreen(Matrix* mat) {
	int i, j;
	printf("[ \n");
	for (i = 0; i < mat->r; i++) {
		printf("  ");
		for (j = 0; j < mat->c; j++) {
			printf("%11.4f ", mat->data[i][j]);
		}
		printf("\n");
	}
	printf("]\n\n");
}

Matrix* createMatrix(int r, int c) {
	int i;
	Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
	if (mat != NULL) {
		mat->r = r;
		mat->c = c;
		mat->data = (double**)malloc(sizeof(double*) * r);
		for (i = 0; i < r; i++) {
			mat->data[i] = (double*)malloc(sizeof(double) * c);
		}
	}

	return mat;
}

void freeMatrix(Matrix* mat) {
	int i;
	//for (i=0;i < mat->r; i++){
	//	free(mat->data[i]);
	//}
	free(mat->data);
}



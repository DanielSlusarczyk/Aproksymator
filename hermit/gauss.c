#include "gauss.h"
#include <math.h>
#include <stdio.h>
#define EPSILON 1e-12


int eliminate(Matrix* mat, Matrix* b) {
	double wsp;
	//Zmienna przechowujaca wspolczynnik
	double maks;
	//Przechowuje maksimum kolumny
	int nr_w;
	//Przechowuje numer wiersza z maksimum kolumny
	double* tmp_data;
	//Zmienna do zamiany wierszy w mat
	double* tmp_b;
	//Zmienna do zamiany wierszy w b
	int i = 0, j = 1, p = 0, k = 0, w=0;
	//Zmienne petli
	if (mat == NULL || b == NULL) {
		printf("Macierze blednie wczytane");
		return 2;
	}
	for (i = 0; i < mat->c - 1; i++) {
		j = i + 1;
		nr_w = i;

		//Selekcja elementu diagonalnego
		maks = mat->data[i][i];
		for (p = i; p < mat->c; p++) {
			if (fabs(mat->data[p][i]) > fabs(maks)) {
				maks = mat->data[p][i];
				nr_w = p;
			}
		}


		//Zamiana wierszy
		tmp_data = mat->data[nr_w];
		tmp_b = b->data[nr_w];
		mat->data[nr_w] = mat->data[j-1];
		b->data[nr_w] = b->data[j-1];
		mat->data[j-1] = tmp_data;
		b->data[j-1] = tmp_b;

		for (j = i + 1; j < mat->c; j++) {
			if (fabs(mat->data[i][i]) < EPSILON)
				return 1;
			wsp = -mat->data[j][i] / mat->data[i][i];
			for (k = i; k <= mat->c; k++) {
				mat->data[j][k] += wsp * mat->data[i][k];
			}
			b->data[j][0] += wsp * (b->data[i][0]);
		}

	}
	//Sprawdzanie macierzy osobliwej -diagonala
	for (w = 0; w < mat->c; w++) {
		if (fabs(mat->data[w][w]) < EPSILON)
			return 1;
	}
	//Sprawdzanie macierzy osobliwej -wiersze
	for (w = 0; w < mat->c; w++) {
		k = 0;
		j = 0;
		for (j = 0; j < mat->c; j++) {
			if (fabs(mat->data[j][w]) < EPSILON)
				k++;
		}
		if (k == mat->c)
			return 1;
	}
	//Sprawdzanie macierzy osobliwej -kolumny
	for (w = 0; w < mat->c; w++) {
		k = 0;
		j = 0;
		for (j = 0; j < mat->c; j++) {
			if (fabs(mat->data[w][j]) < EPSILON)
				k++;
		}
		if (k == mat->c)
			return 1;
	}

	printf("\nPo eliminacji Gaussa:\n\n");
	printToScreen(mat);
	printToScreen(b);
	return 0;
}


#include "backsubst.h"
#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	double sum;
	if (x->r != mat->r || x->r != b->r || b->r != mat->r || b->c != 1 || x->c != 1 || mat->c != mat->r) {
		fprintf(stderr, "Nieodpowiedni rozmiar macierzy.");
		return 2;
	}
	for (int j = 0; j < mat->r; j++) {
		if (mat->data[j][j] == 0) {
			fprintf(stderr, "Blad dzielenia przez zero.");
			return 1;
		}
	}
	x->data[x->r - 1][0] = b->data[b->r - 1][0] / mat->data[mat->r - 1][mat->c - 1];
	
	for (int i = (mat->r) - 2; i >= 0; i--) {
		sum = 0.0;
		for (int j = (mat->c) - 1;j > i; j--) {
			sum += (mat->data[i][j]) * x->data[j][0];
		}
		x->data[i][0] = (b->data[i][0] - sum) / mat->data[i][i];
	}

	return 0;
}

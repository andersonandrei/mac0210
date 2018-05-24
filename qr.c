#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void mtransposta(float **m, float **t, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			t[i][j] = m[j][i];
		}
	}
	return;
}

float vnorma(float *v, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++){
		sum += (v[i] * v[i]);
	}
	return sqrt(sum);
}

float

void granS(float **m, float **base_ortn) {


}
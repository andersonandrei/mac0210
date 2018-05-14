#include <stdio.h>
#include <stdlib.h>

void matrixAsVector(float *v, int n) {
	for (int i = 0; i < n*n; i++) {
		printf("Insira o %d elemento da matriz: ",i%n);
		scanf("%f",&v[i]);
	}
	return;
}

void printMatriz(float *v, int n) {
	for(int i = 0; i < n*n; i++) {
		if(i%n == 0	) printf("\n");
		printf("%f ", v[i]);
	}
	printf("\n");
	return;
}

void lu(float *v, int n) {
	printf("\n LU started ... \n");
	printMatriz(v,n);
	fflush(stdout);
	int i, j, k, l;
	float alfa;
	for (i = *v-1; i < n*n; i+=n+1){
		printf("\n i = %d", i); fflush(stdout);
		for (j=i+n; j < n*n; j+=n){
			printf("\n 		j = %d", j); fflush(stdout);
			printf("\n 		v[j] = %f e v[i] = %f", v[j],v[i]); fflush(stdout);
			alfa = v[j] / v[i];
			printf("\n 		Calculou alfa = %f", alfa);fflush(stdout);
			for (k = j, l = i; k < j+n; k++, l++) {
				printf("\n 			k = %d", k); fflush(stdout);
				printf("\n 			l = %d", l); fflush(stdout);
				printf("\n 			v[k] = %f e v[l] = %f", v[k],v[l]); fflush(stdout);
				v[k] += v[l] * ((-1) * (alfa));
				printf("\n 			v[k] = %f ", v[k]); fflush(stdout);
			}
			v[j] = alfa;
		}
	}
	return;
}

int main() {
	printf("\n******************************************");
	printf("\n Esse programa calcula a fatoracao LU da");
	printf("\n matriz Inserida e exibe, dentro de uma "); 
	printf("\n mesma matriz a L na triangular inferior"); 
	printf("\n e a U na triangular superior. ");
	printf("\n******************************************");

	int n;
	float *v;

	printf("\n Insira a dimensao da matriz quadrada: ");
	scanf("%d", &n);

	v = malloc (n * sizeof(int));

	matrixAsVector(v, n);
	lu(v, n);
	printf("\n Matriz resulante: \n");
	printMatriz(v,n);

	return 0;
}
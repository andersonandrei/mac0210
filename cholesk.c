#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printaMatriz(float *m, int n) {
	printf("\n---------------------\n");
	for (int i = 0; i < n*n; i+=1) {
		if(i % n == 0) printf("\n");
		printf("%f ", m[i]);
	}
	printf("\n");
}

void cholesky(float *m, int n) {
	int i, j, k, l, q;
	int ij, jk, ik, kk, cont;
	ij = 0;
	jk = 0;
	ik = 0;
	kk = 0;
	float sum;
	for (int i = 0; i < n*n; i++) printf("%f, ", m[i]);
	for (int i = 0; i < n; i++) {
		printf("\n i = %d", i);
		cont = 0;
		for (int j = 0; j <= i; j++) {
			printf("\n      j = %d", j);
			printf("\n 						ij = %d", ij);
			if(i == j) {
				jk = ij;
				sum = 0;
				for (k = 0; k < j; k++) {
					printf("\n          k1 = %d", k);
					sum += pow(m[ij],2);
					//printf("\n          sum1 = %f", sum);
					jk++;
				} 
				m[ij] = sqrt(m[ij] - sum);
				//printf("\n          calculou: m[%d] = %f", ij,m[ij]);
			}

			else {
				jk = ij;
				sum = 0;
				for (k = 0; k < j; k++) {
					printf("\n          k2 = %d", k);
					sum += m[ij] * m[jk];
					//printf("\n          calculou: m[%d] = %f -- m[%d] = %f", ij,m[ij], jk,m[jk]);
					jk++;
				}
				m[jk] = 1/m[ij] - sum; 
			}

			ij++;
			cont++;
		}
		ij+=n;
		ij-= cont;
	}

	printf(" Lower Triangular\n"); 
    
    for (int i = 0; i < n*n; i++) {
        // Lower Triangular
        if(i%n == 0) printf("\n");
        printf("%f ",m[i]);
    }
}

// Driver Code
int main()
{
    int n = 3;
    //float *m;
    //m = malloc(n*n * sizeof(float));
    float m[9] = {4, 12, -16, 12, 37, -43, -16, -43, 98 };
    cholesky(m, n);
    return 0;
}
//------------------------------------------------------------------------------
// para compilar o programa de testes, substitua a lu_fajuta pela sua e execute
//
// gcc main.c ep2_test.c -lm -o ep2
//
// e depois, faça
//
// ./ep2
//
// para executar os testes
//------------------------------------------------------------------------------

#include "ep2_test.h"


void palu(float *m, int n, int *p) {
	int i, j, k, l;
	float alfa, aux;
	int i_max, linha_a, linha_b, aux_int ;

	for (int i = 0; i < n; i++) p[i] = i;
	
	for (i = 0; i< n*n; i+=n+1) {
		i_max = i;
		//printf("\nOlhando pro pivo: %f", m[i]);

		for (j = i+n; j < n*n; j+=n) {
			if (fabs(m[j]) > fabs(m[i])) {
				//printf("\n Pos : m[%d] : %f eh maior", j, m[j]);
				i_max = j;
			}
		} 
		if (i_max != i) {
				//printf("\n Trocar : m[%d] : %f ", i_max, m[i_max]);
				int start_a, start_b;
				start_a = i;
				start_b = i_max;

				linha_a = i/3;
				linha_b = i_max/3;
				aux_int = p[linha_a];
				p[linha_a] = p[linha_b];
				p[linha_b] = aux_int;
				
				while(start_a < i+n) {
					aux = m[start_a];
					m[start_a] = m[start_b];
					m[start_b] = aux;
					start_a++;
					start_b++;
				}
		}

		for (j = i+n ; j < n*n; j+=n) {

			//printf("\n	Olhando pro j: %f", m[j]);
			
			if (m[j] != 0) alfa = m[j] / m[i];
			else alfa = 1 ;
			for (k = j, l = i; k < j+n; k++, l++) {
				//printf("\n		Olhando pro k: %d", k);
				
				//printf("\n		Alfa k : %f", alfa);
				//printf("\n		m[%d] : %f e m[%d] : %f", k, m[k], l, m[l]);
				m[k] += m[l] * ((-1) * (alfa));
				//printf("\n		m[%d] : %f", k, m[k]);
			}
			m[j] = alfa;
		}
	}

	return;
}


int main()
{
  ep2_test(palu);
  return 0;
}

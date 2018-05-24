#include <math.h>
#include <float.h>
#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "ep2_test.h"

//------------------------------------------------------------------------------
// alguns geradores de matrizes aleatorias
//------------------------------------------------------------------------------

typedef int (*preenche)(double* a, int param);

typedef struct
{
  int param;
  preenche gere;
} gerador;

int matrix_nula(double* a, int n)
{
  int volume = n * n;
  for(int k = 0; k < volume; ++k, ++a)
  {
    *a = 0;
  }

  return n;
}

int matrix_de_uns(double* a, int n)
{
  int volume = n * n;
  for(int k = 0; k < volume; ++k, ++a)
  {
    *a = 1;
  }

  return n;
}

int matrix_aleatoria(double* a, int n)
{
  int volume = n * n;
  for(int k = 0; k < volume; ++k, ++a)
  {
    *a = (rand() & 0x3FF) - 0x2FF;  // gerando ints com sinal com 12 bits,
  }

  return n;
}

//------------------------------------------------------------------------------
// permute_linhas atribui a linha p[i] da matrix src à linha i da matriz dst
//------------------------------------------------------------------------------

void permute_linhas(double* dst, double const* src, int n, int const* p)
{
  int row_size = n * sizeof(double);

  for(int i = 0; i < n; ++i, dst += n, ++p)
  {
    memcpy(dst, src + *p * n, row_size);
  }
}

void teste_permute_linhas()
{
  int p[3] = {1,2,0};
  double src[9] = {1,2,3,4,5,6,7,8,9};
  double dst[9];
  permute_linhas(dst, src, 3, p);

  assert((dst[0] == 4) && (dst[1] == 5) && (dst[2] == 6) ); // linha[0] de dst = linha[1] de src
  assert((dst[3] == 7) && (dst[4] == 8) && (dst[5] == 9) ); // linha[1] de dst = linha[2] de src
  assert((dst[6] == 1) && (dst[7] == 2) && (dst[8] == 3) ); // linha[2] de dst = linha[0] de src
}

//------------------------------------------------------------------------------
// mul_lu(dst, src, int) assume que src contém l e u no formato descrito na
// aula e escreve l * u em dst
//------------------------------------------------------------------------------

void mul_lu(double* dst, double const* src, int n)
{
  double const* linha = src;
  for(int i = 0; i < n; ++i, linha += n) {

    double const* coluna = src;

    for(int j = 0; j < i; ++j, ++coluna) {

      double const* linha2  = linha;
      double const* coluna2 = coluna;
      double aij = *linha2 * *coluna2;

      for(int k = 0; k < j; ++k) {
        aij += *(++linha2) * *(coluna2 += n);
      }

      *dst++ = aij;
    }

    for(int j = i; j < n; ++j, ++coluna) {

      double aij = 0;
      double const* linha2  = linha;
      double const* coluna2 = coluna;

      for(int k = 0; k < i; ++k, ++linha2, (coluna2 += n)) {
        aij += *linha2 * *coluna2;
      }

      *dst++ = aij + *coluna2;
    }
  }
}

//------------------------------------------------------------------------------
// mul_lu com indices, para testes
//------------------------------------------------------------------------------

void mu_lu_com_indices(double* dst, double const* src, int n)
{
  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < n; ++j)
    {
      double aij = 0;

      for(int k = 0; k < n; ++k)
      {
        double ukj = (j >= k) ? src[k * n + j] : 0;
        double lik = (k <  i) ? src[i * n + k] : ((k == i) ? 1 : 0);
        aij += lik * ukj;
      }

      dst[i * n + j] = aij;
    }
  }
}

void teste_mul_lu()
{
  double dst[25];
  double src[25] = {-1,  2,  3,  4 , 5,  6,  7,  8,  9};

  mul_lu(dst, src, 1);
  assert( dst[0] == - 1);

  mul_lu(dst, src, 2);
  assert( (dst[0] == -1) && (dst[1] == 2)  ); // primeira linha
  assert( (dst[2] == -3) && (dst[3] == 10) ); // primeira linha

  double lu[25]  = {-1,  2,  3, -4, 13, 18, -7, 54, 78}; // calculada na mao
  mul_lu(dst, src, 3);

  assert((dst[0] == lu[0]) && (dst[1] == lu[1]) && (dst[2] == lu[2]) ); // linha[0] de dst = linha[0] de lu
  assert((dst[3] == lu[3]) && (dst[4] == lu[4]) && (dst[5] == lu[5]) ); // linha[1] de dst = linha[1] de lu
  assert((dst[6] == lu[6]) && (dst[7] == lu[7]) && (dst[8] == lu[8]) ); // linha[2] de dst = linha[2] de lu

  // alguns testes aleatorios

  for(int n = 1; n < 6; ++n) {
    for(int k = 0; k < 10; ++k) {
      matrix_aleatoria(src, n);
      mul_lu(dst, src, n);
      mu_lu_com_indices(lu, src, n);
      for(int j = 0; j < n * n; ++j)
        assert( dst[j] == lu[j]);
    }
  }
}

void teste(lu a_testar, gerador* exemplo, int n_exemplos)
{
  // matrizes com tamanho no maximo 16

  int p[16];
  double* memoria = (double*) malloc(4 * 16* 16 * sizeof(double));
  double* a = memoria;
  double* copia = memoria + 16 * 16;
  double* l_x_u = copia   + 16 * 16;
  double* pa    = l_x_u   + 16 * 16;

  int falhas = 0;
  for(int i  = 0; i < n_exemplos; ++i)
  {
    int n = exemplo[i].gere(a, exemplo[i].param);
    int volume = n * n;
    memcpy(copia, a, volume * sizeof(double));

    a_testar(a, n, p);

    permute_linhas(pa, copia, n, p);
    mul_lu(l_x_u, a, n);

    for(int k = 0; k < volume; ++k)
    {
      double erro = fabs(pa[k] - l_x_u[k]);
      if( erro > 1.0e-8 )
      {
        ++falhas;
        printf("O teste %d encontrou um erro de %g\n", i, erro);
        break;
      }
    }
  }

  printf("%d testes encontram erros\n", falhas);
  printf("%d testes não encontram erros\n", n_exemplos - falhas);
  free(memoria);
}

void ep2_test(lu a_testar)
{
  srand(10); // iniciando o gerador de numeros aleatorios

  gerador g[50];
  gerador* pg = g;

  // gerando 25 matrizes aleatorias
  for(int k = 1; k < 6; ++k)
  {
    for(int j = 0; j < 5; ++j, ++pg)
    {
      pg->param = k;
      pg->gere = matrix_aleatoria;
    }
  }

  // gerando 5 matrizes nulas
  for(int k = 1; k < 6; ++k, ++pg)
  {
    pg->param = k;
    pg->gere = matrix_nula;
  }

  // gerando 5 matrizes com todas entradas iguais a 1
  for(int k = 1; k < 6; ++k, ++pg)
  {
    pg->param = k;
    pg->gere = matrix_de_uns;
  }

  teste(a_testar, g, 35);
}

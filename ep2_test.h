//------------------------------------------------------------------------------
// veja o arquivo main.c para um exemplo de como testar o seu ep
//------------------------------------------------------------------------------

#ifndef EP2_TEST_H
#define EP2_TEST_H

typedef void (*lu)(double* matrix, int n, int* permutacao);

void ep2_test(lu seu_ep);

#endif // EP2_TEST_H

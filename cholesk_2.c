// CPP program to decompose a matrix using
// Cholesky Decomposition
//#include <bits/stdc++.h>
//using namespace std;
 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

void Cholesky_Decomposition(int matrix[][MAX], int n)
{
    int lower[n][n];
    //memset(lower, 0, sizeof(lower));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
            lower[i][j] = 0;
 
    // Decomposing a matrix into Lower Triangular
    for (int i = 0; i < n; i++) {
        printf("\n i = %d", i);
        for (int j = 0; j <= i; j++) {
            printf("\n      j = %d", j);
            int sum = 0;
 
            if (j == i) // summation for diagnols
            {
                for (int k = 0; k < j; k++){
                    printf("\n          k1 = %d", k);
                    sum += pow(lower[j][k], 2);
                }
                lower[j][j] = sqrt(matrix[j][j] - sum);
            } 
            else {
 
                // Evaluating L(i, j) using L(j, j)
                for (int k = 0; k < j; k++) {
                    printf("\n          k2 = %d", k);
                    sum += (lower[i][k] * lower[j][k]);
                }
                lower[i][j] = (matrix[i][j] - sum) / lower[j][j];
            }
        }
    }
 
    // Displaying Lower Triangular and its Transpose
    printf(" Lower Triangular\n"); 
    
    for (int i = 0; i < n; i++) {
         
        // Lower Triangular
        for (int j = 0; j < n; j++)
            printf("%d ",lower[i][j]);
        printf("\n");
    }
    printf("Transpose\n");
    for (int i = 0; i < n; i++) {    
        // Transpose of Lower Triangular
        for (int j = 0; j < n; j++)
            printf("%d ",lower[j][i]);
        printf("\n");
    }
}
 
// Driver Code
int main()
{
    int n = 3;
    int matrix[][MAX] = { { 4, 12, -16 },
                        { 12, 37, -43 },
                        { -16, -43, 98 } };
    Cholesky_Decomposition(matrix, n);
    return 0;
}
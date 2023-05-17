#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 600
#define NUM_THREADS 6

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main() {
    // Initialize matrices A and B with random values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 10;
            B[i][j] = 10;
        }
    }
int i,j,k;
    omp_set_num_threads(NUM_THREADS);
 
    double start_time = omp_get_wtime();
    
     #pragma omp parallel for shared(A,B,C) private(i,j,k) num_threads(6)
    for ( i = 0; i < SIZE; i++) {
        for ( j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for ( k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    double end_time = omp_get_wtime();
    
     for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
	double omp_parallel_time = (double)(end_time - start_time);
	printf("Parallel omp execution time: %f seconds\n", omp_parallel_time);
    return 0;
}

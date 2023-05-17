#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 600
#define N 600
#define P 600

int **matrix_a;
int **matrix_b;
int **matrix_c;

void multiply_row(int i) {
    int j, k;
    for (j = 0; j < P; j++) {
        matrix_c[i][j] = 0;
        for (k = 0; k < N; k++) {
            matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        }
    }
}

int main() {
    matrix_a = malloc(M * sizeof(int *));
    matrix_b = malloc(N * sizeof(int *));
    matrix_c = malloc(M * sizeof(int *));
    int i, j;
    for (i = 0; i < M; i++) {
        matrix_a[i] = malloc(N * sizeof(int));
        matrix_c[i] = malloc(P * sizeof(int));
        for (j = 0; j < N; j++) {
            matrix_a[i][j] = 10;
        }
    }
    for (i = 0; i < N; i++) {
        matrix_b[i] = malloc(P * sizeof(int));
        for (j = 0; j < P; j++) {
            matrix_b[i][j] = 10;
        }
    }

    // Calculate sequential execution time
    clock_t sequential_start = clock();

    for (i = 0; i < M; i++) {
        multiply_row(i);
    }

    // Calculate sequential execution time
    clock_t sequential_end = clock();

    double sequential_time = (double)(sequential_end - sequential_start) / CLOCKS_PER_SEC;



    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", matrix_c[i][j]);
        }
        printf("\n");
    }
        printf("Sequential execution time: %f seconds\n", sequential_time);

    for (i = 0; i < M; i++) {
        free(matrix_a[i]);
        free(matrix_c[i]);
    }
    for (i = 0; i < N; i++) {
        free(matrix_b[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(matrix_c);

    return 0;
}


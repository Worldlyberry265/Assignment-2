#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 600
#define NUM_THREADS 6

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void *multiply(void *arg) {
    int thread_id = (int)arg;
    int start = (SIZE / NUM_THREADS) * thread_id;
    int end = start + (SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize matrices A and B with random values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 10;
            B[i][j] = 10;
        }
    }

    // Create and join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, multiply, (void *)i);
    }
    // Measure parallel execution time
    clock_t parallel_start = clock();

     for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Measure parallel execution time
    clock_t parallel_end = clock();

    double parallel_time = (double)(parallel_end - parallel_start) / CLOCKS_PER_SEC;
   
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("Parallel execution time: %f seconds\n", parallel_time);

    return 0;
}

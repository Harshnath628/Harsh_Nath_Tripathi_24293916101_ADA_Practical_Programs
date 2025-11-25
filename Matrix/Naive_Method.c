#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for 2D array
int** get_allocated(int r, int c) {
    int** arr = (int**)calloc(r, sizeof(int*));
    if (!arr) { printf("Error: Memory Allocation failed!"); exit(-1); }
    for (int i = 0; i < r; i++) {
        arr[i] = (int*)calloc(c, sizeof(int));
        if (!arr[i]) { printf("Error: Memory Allocation failed!"); exit(-1); }
    }
    return arr;
}

// Fill array with random integers
void fill_random(int** arr, int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            arr[i][j] = rand() % 100;
}

// Naive matrix multiplication
int** get_product_2d_array_naive(int** a, int r1, int c1, int** b, int r2, int c2) {
    if (c1 != r2) {
        printf("Error!: Matrix multiplication not possible due to unmatched dimensions\n");
        exit(-1);
    }
    int **c = get_allocated(r1, c2);
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

int main() {
    srand(time(NULL));

    // Matrix sizes to test (n x n)
    int sizes[] = {10, 50, 100, 200, 300, 400, 500};
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];

        int** a = get_allocated(n, n);
        int** b = get_allocated(n, n);

        fill_random(a, n, n);
        fill_random(b, n, n);

        clock_t start = clock();
        for (int r = 0; r < 5; r++) { // repeat multiple times for averaging
            int** c = get_product_2d_array_naive(a, n, n, b, n, n);
            // Free c after each run
            for (int i = 0; i < n; i++) free(c[i]);
            free(c);
        }
        clock_t end = clock();

        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time = elapsed / 5.0; // average over repetitions

        printf("%d\t%.6f\n", n, avg_time);

        // Free matrices a and b
        for (int i = 0; i < n; i++) {
            free(a[i]);
            free(b[i]);
        }
        free(a);
        free(b);
    }

    return 0;
}

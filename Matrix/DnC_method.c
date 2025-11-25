#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for 2D square matrix
int** get_allocated(int n) {
    int** arr = (int**)calloc(n, sizeof(int*));
    if (!arr) { printf("Error: Memory Allocation failed!\n"); exit(-1); }
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)calloc(n, sizeof(int));
        if (!arr[i]) { printf("Error: Memory Allocation failed!\n"); exit(-1); }
    }
    return arr;
}

// Fill matrix with random integers
void fill_random(int** arr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % 100;
}

// Naive multiplication (used as base case)
int** multiply_naive(int** A, int** B, int n) {
    int** C = get_allocated(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Add two matrices
int** add_matrix(int** A, int** B, int n) {
    int** C = get_allocated(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Subtract two matrices
int** sub_matrix(int** A, int** B, int n) {
    int** C = get_allocated(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Divide & Conquer multiplication
int** multiply_DC(int** A, int** B, int n) {
    if (n <= 64) { // base case: naive multiplication
        return multiply_naive(A, B, n);
    }

    int k = n / 2;

    // Allocate submatrices
    int** A11 = get_allocated(k); int** A12 = get_allocated(k);
    int** A21 = get_allocated(k); int** A22 = get_allocated(k);
    int** B11 = get_allocated(k); int** B12 = get_allocated(k);
    int** B21 = get_allocated(k); int** B22 = get_allocated(k);

    // Split A and B
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // Perform 8 recursive multiplications
    int** M1 = multiply_DC(A11, B11, k);
    int** M2 = multiply_DC(A12, B21, k);
    int** M3 = multiply_DC(A11, B12, k);
    int** M4 = multiply_DC(A12, B22, k);
    int** M5 = multiply_DC(A21, B11, k);
    int** M6 = multiply_DC(A22, B21, k);
    int** M7 = multiply_DC(A21, B12, k);
    int** M8 = multiply_DC(A22, B22, k);

    // Combine results into final matrix
    int** C = get_allocated(n);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]       = M1[i][j] + M2[i][j];       // C11
            C[i][j+k]     = M3[i][j] + M4[i][j];       // C12
            C[i+k][j]     = M5[i][j] + M6[i][j];       // C21
            C[i+k][j+k]   = M7[i][j] + M8[i][j];       // C22
        }
    }

    return C;
}

int main() {
    srand(time(NULL));

    int sizes[] = {2,8,16,32,64, 128, 256,1024}; // powers of 2 for divide & conquer
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];
        int** A = get_allocated(n);
        int** B = get_allocated(n);
        fill_random(A, n);
        fill_random(B, n);

        clock_t start = clock();
        for (int r = 0; r < 3; r++) { // repeat for averaging
            int** C = multiply_DC(A, B, n);

            // Free result matrix
            for (int i = 0; i < n; i++) free(C[i]);
            free(C);
        }
        clock_t end = clock();

        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time = elapsed / 3.0;

        printf("%d\t%.6f\n", n, avg_time);

        // Free A, B
        for (int i = 0; i < n; i++) { free(A[i]); free(B[i]); }
        free(A); free(B);
    }

    return 0;
}

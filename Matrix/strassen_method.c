#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for 2D array
int** get_allocated(int n) {
    int** arr = (int**)calloc(n, sizeof(int*));
    if (!arr) { printf("Error: Memory Allocation failed!"); exit(-1); }
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)calloc(n, sizeof(int));
        if (!arr[i]) { printf("Error: Memory Allocation failed!"); exit(-1); }
    }
    return arr;
}

// Fill matrix with random numbers
void fill_random(int** arr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % 100;
}

// Naive multiplication (used as base case in Strassen)
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

// Strassen multiplication
int** strassen(int** A, int** B, int n) {
    if (n <= 64) { // base case → naive multiplication
        return multiply_naive(A, B, n);
    }

    int k = n / 2;

    // Allocate submatrices
    int** A11 = get_allocated(k); int** A12 = get_allocated(k);
    int** A21 = get_allocated(k); int** A22 = get_allocated(k);
    int** B11 = get_allocated(k); int** B12 = get_allocated(k);
    int** B21 = get_allocated(k); int** B22 = get_allocated(k);

    // Split matrices
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

    // Compute 7 products using Strassen’s formulas
    int** M1 = strassen(add_matrix(A11, A22, k), add_matrix(B11, B22, k), k);
    int** M2 = strassen(add_matrix(A21, A22, k), B11, k);
    int** M3 = strassen(A11, sub_matrix(B12, B22, k), k);
    int** M4 = strassen(A22, sub_matrix(B21, B11, k), k);
    int** M5 = strassen(add_matrix(A11, A12, k), B22, k);
    int** M6 = strassen(sub_matrix(A21, A11, k), add_matrix(B11, B12, k), k);
    int** M7 = strassen(sub_matrix(A12, A22, k), add_matrix(B21, B22, k), k);

    // Combine results
    int** C = get_allocated(n);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j+k] = M3[i][j] + M5[i][j];
            C[i+k][j] = M2[i][j] + M4[i][j];
            C[i+k][j+k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

int main() {
    srand(time(NULL));

    int sizes[] = {2,8,16,32,64, 128, 256, 512,1024};  // Strassen works well with powers of 2
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
        for (int r = 0; r < 3; r++) { // repeat 3 times for averaging
            int** C = strassen(A, B, n);

            // Free C
            for (int i = 0; i < n; i++) free(C[i]);
            free(C);
        }
        clock_t end = clock();

        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time = elapsed / 3.0;

        printf("%d\t%.6f\n", n, avg_time);

        // Free A, B
        for (int i = 0; i < n; i++) {
            free(A[i]); free(B[i]);
        }
        free(A); free(B);
    }

    return 0;
}

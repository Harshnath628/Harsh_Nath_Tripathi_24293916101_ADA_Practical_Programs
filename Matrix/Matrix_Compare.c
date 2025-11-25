#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ----------- Utility Functions ------------

// Allocate n x n matrix
int** allocate_matrix(int n) {
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        arr[i] = (int*)calloc(n, sizeof(int));
    return arr;
}

// Free matrix
void free_matrix(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

// Fill matrix with random values
void fill_random(int** arr, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % 10;
}

// Add matrices
int** add_matrix(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Subtract matrices
int** sub_matrix(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// ----------- Naive O(n^3) ------------
int** multiply_naive(int** A, int** B, int n) {
    int** C = allocate_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// ----------- Divide & Conquer O(n^3) ------------
int** multiply_DC(int** A, int** B, int n) {
    if (n <= 32) return multiply_naive(A, B, n);

    int k = n / 2;
    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);

    for (int i = 0; i < k; i++)
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

    int** C = allocate_matrix(n);
    int** M1 = multiply_DC(A11, B11, k);
    int** M2 = multiply_DC(A12, B21, k);
    int** M3 = multiply_DC(A11, B12, k);
    int** M4 = multiply_DC(A12, B22, k);
    int** M5 = multiply_DC(A21, B11, k);
    int** M6 = multiply_DC(A22, B21, k);
    int** M7 = multiply_DC(A21, B12, k);
    int** M8 = multiply_DC(A22, B22, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j]     = M1[i][j] + M2[i][j];
            C[i][j+k]   = M3[i][j] + M4[i][j];
            C[i+k][j]   = M5[i][j] + M6[i][j];
            C[i+k][j+k] = M7[i][j] + M8[i][j];
        }
    return C;
}

// ----------- Strassen O(n^2.81) ------------
int** multiply_strassen(int** A, int** B, int n) {
    if (n <= 32) return multiply_naive(A, B, n);

    int k = n / 2;
    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);

    for (int i = 0; i < k; i++)
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

    int** P1 = multiply_strassen(add_matrix(A11, A22, k), add_matrix(B11, B22, k), k);
    int** P2 = multiply_strassen(add_matrix(A21, A22, k), B11, k);
    int** P3 = multiply_strassen(A11, sub_matrix(B12, B22, k), k);
    int** P4 = multiply_strassen(A22, sub_matrix(B21, B11, k), k);
    int** P5 = multiply_strassen(add_matrix(A11, A12, k), B22, k);
    int** P6 = multiply_strassen(sub_matrix(A21, A11, k), add_matrix(B11, B12, k), k);
    int** P7 = multiply_strassen(sub_matrix(A12, A22, k), add_matrix(B21, B22, k), k);

    int** C = allocate_matrix(n);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j]     = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C[i][j+k]   = P3[i][j] + P5[i][j];
            C[i+k][j]   = P2[i][j] + P4[i][j];
            C[i+k][j+k] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    return C;
}

// ----------- Main Program ------------
int main() {
    srand(time(NULL));
    int sizes[] = {2,8,16,32,128,256,512,1024}; // test powers of 2
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    printf("n\tNaive(s)\tDivide&Conquer(s)\tStrassen(s)\n");
    printf("---------------------------------------------------\n");

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];
        int** A = allocate_matrix(n);
        int** B = allocate_matrix(n);
        fill_random(A, n);
        fill_random(B, n);

        clock_t start, end;

        start = clock();
        int** C1 = multiply_naive(A, B, n);
        end = clock();
        double time_naive = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        int** C2 = multiply_DC(A, B, n);
        end = clock();
        double time_dc = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        int** C3 = multiply_strassen(A, B, n);
        end = clock();
        double time_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\t\t%.6f\n", n, time_naive, time_dc, time_strassen);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C1, n);
        free_matrix(C2, n);
        free_matrix(C3, n);
    }

    return 0;
}

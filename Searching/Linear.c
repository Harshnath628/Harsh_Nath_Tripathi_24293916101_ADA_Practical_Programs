#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Linear search function
int get_index_linear_search(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

// Fill array with random numbers
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main() {
    // Different input sizes
    int n_values[] = {10, 50, 100, 500, 1000, 3000, 5000, 6000, 7000, 8000};
    int num_cases = sizeof(n_values) / sizeof(n_values[0]);
    int runs = 1000; // number of repetitions per case

    srand(time(NULL)); // Seed random generator

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int case_i = 0; case_i < num_cases; case_i++) {
        int n = n_values[case_i];
        int *arr = (int *)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed for n=%d\n", n);
            continue;
        }

        clock_t start = clock();

        for (int i = 0; i < runs; i++) {
            fillRandom(arr, n);
            int key = arr[n - 1]; // search worst case (last element)
            get_index_linear_search(arr, n, key);
        }

        clock_t end = clock();
        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / runs;

        printf("%d\t%.8f\n", n, avg_time);

        free(arr);
    }

    return 0;
}

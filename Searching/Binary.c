#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search with dummy loop for amplification
int get_index_binary_search(int arr[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Dummy loop to increase measurable time
        for (int k = 0; k < 1000; k++);

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Fill array with sorted values (since binary search needs sorted input)
void fillSorted(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;   // strictly increasing sequence
}

int main() {
    // Updated larger n values
    int nValues[] = {100, 500, 1000, 5000, 10000, 30000, 50000, 60000, 70000, 80000};
    int numTests = sizeof(nValues) / sizeof(nValues[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int t = 0; t < numTests; t++) {
        int n = nValues[t];
        int* arr = (int*)malloc(n * sizeof(int));
        if (!arr) {
            printf("Memory Allocation failed for n = %d!\n", n);
            continue;
        }

        fillSorted(arr, n);

        // Worst-case key (not in array)
        int key = arr[n - 1] + 1;

        clock_t start = clock();
        for (int i = 0; i < 1000; i++) {
            get_index_binary_search(arr, n, key);
        }
        clock_t end = clock();

        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / 1000;
        printf("%d\t%f\n", n, avg_time);

        free(arr);
    }

    return 0;
}

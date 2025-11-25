#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursive Fibonacci
int fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    // Input sizes for measurement
    int n_values[] = {5, 10, 15, 20, 25, 30, 32, 34, 36, 38, 40};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];
        double total_time = 0.0;
        int runs = 3;  // average over a few runs for stability

        for (int j = 0; j < runs; j++) {
            clock_t start = clock();
            fib_recursive(n);  // measure recursive computation
            clock_t end = clock();
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        double avg_time = total_time / runs;
        printf("%d\t%lf\n", n, avg_time);
    }

    return 0;
}

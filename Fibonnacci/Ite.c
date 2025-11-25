#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Iterative Fibonacci function
int fib_iterative(int n) {
    if (n <= 1)
        return n;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    // Input sizes for testing
    int n_values[] = {10, 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];
        double total_time = 0.0;
        int runs = 5;               // Average over multiple runs for better accuracy
        int repeat_factor = 100000; // Amplify workload to make measurable

        for (int j = 0; j < runs; j++) {
            clock_t start = clock();

            for (int k = 0; k < repeat_factor; k++) {
                fib_iterative(n); // repeat many times
            }

            clock_t end = clock();
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        double avg_time = total_time / runs / repeat_factor;
        printf("%d\t%.10f\n", n, avg_time);
    }

    return 0;
}

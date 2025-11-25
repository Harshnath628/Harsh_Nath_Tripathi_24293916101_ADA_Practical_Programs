#include <stdio.h>
#include <windows.h>
#define MAX 100000
#define REPEAT 100000  // Repeat count for timing accuracy

long long fib_dp[MAX];

// ----------------------
// Bottom-Up DP Fibonacci
// ----------------------
long long fib_bottom_up(int n) {
    if (n <= 1)
        return n;

    fib_dp[0] = 0;
    fib_dp[1] = 1;

    for (int i = 2; i <= n; i++)
        fib_dp[i] = fib_dp[i - 1] + fib_dp[i - 2];

    return fib_dp[n];
}

// ----------------------
// High-Precision Timer
// ----------------------
double get_time_seconds() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
}

// ----------------------
// Main Function
// ----------------------
int main() {
    int n_values[] = {10, 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000};
    int num_cases = sizeof(n_values) / sizeof(n_values[0]);

    printf("n\t\tAverage_Runtime(seconds)\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < num_cases; i++) {
        int n = n_values[i];

        double start = get_time_seconds();

        // Repeat multiple times for reliable average
        for (int r = 0; r < REPEAT; r++) {
            fib_bottom_up(n);
        }

        double end = get_time_seconds();

        double total_time = end - start;
        double avg_time = total_time / REPEAT;

        printf("%d\t\t%.10lf\n", n, avg_time);
    }

    return 0;
}

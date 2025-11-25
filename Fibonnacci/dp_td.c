#include <stdio.h>
#include <windows.h>
#define MAX 100000
#define REPEAT 100000  // Number of repetitions to make timing visible

long long memo[MAX];

// ----------------------
// Top-Down DP Fibonacci
// ----------------------
long long fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
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

        // Reset memoization array
        for (int j = 0; j <= n; j++)
            memo[j] = -1;

        double start = get_time_seconds();

        // Repeat multiple times for average runtime
        for (int r = 0; r < REPEAT; r++) {
            fib(n);
        }

        double end = get_time_seconds();

        double total_time = end - start;
        double avg_time = total_time / REPEAT;

        printf("%d\t\t%.10lf\n", n, avg_time);
    }

    return 0;
}

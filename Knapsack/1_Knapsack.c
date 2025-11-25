#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  // for high-precision timing

#define MAX 10000

int maxx(int a, int b) {
    return (a > b) ? a : b;
}

int knapSack(int W, int wt[], int val[], int n) {
    // dynamically allocate DP table
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = maxx(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int result = dp[n][W];
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);

    return result;
}

// high-precision timer for Windows
double get_time_diff(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
}

int main() {
    int n_values[] = {100, 300, 500, 700, 1000, 2000};
    int W_values[] = {500, 800, 1200, 2000, 3000, 4000};

    srand((unsigned)time(NULL));
    printf("0/1 KNAPSACK (DYNAMIC PROGRAMMING - BOTTOM UP)\n");
    printf("-------------------------------------------------\n");
    printf("%-10s %-12s %-20s\n", "Items(n)", "Capacity(W)", "Avg Time (seconds)");
    printf("-------------------------------------------------\n");

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    for (int t = 0; t < 6; t++) {
        int n = n_values[t];
        int W = W_values[t];

        int wt[MAX], val[MAX];
        for (int i = 0; i < n; i++) {
            wt[i] = rand() % 100 + 1;
            val[i] = rand() % 1000 + 10;
        }

        double total_time = 0.0;
        int runs = 3;

        for (int r = 0; r < runs; r++) {
            LARGE_INTEGER start, end;
            QueryPerformanceCounter(&start);

            knapSack(W, wt, val, n);

            QueryPerformanceCounter(&end);
            total_time += get_time_diff(start, end, freq);
        }

        double avg_time = total_time / runs;
        printf("%-10d %-12d %-20lf\n", n, W, avg_time);
    }

    return 0;
}

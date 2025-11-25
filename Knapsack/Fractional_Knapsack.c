#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for items
struct Item {
    int value, weight;
    double ratio;
};

// Comparison function for sorting by ratio
int compare(const void *a, const void *b) {
    double r1 = ((struct Item*)a)->ratio;
    double r2 = ((struct Item*)b)->ratio;
    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    return 0;
}

// Fractional Knapsack Function
double fractionalKnapsack(struct Item arr[], int n, int W) {
    qsort(arr, n, sizeof(struct Item), compare);

    double totalValue = 0.0;
    int remaining = W;

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= remaining) {
            totalValue += arr[i].value;
            remaining -= arr[i].weight;
        } else {
            totalValue += arr[i].ratio * remaining;
            break;
        }
    }
    return totalValue;
}

int main() {
    int nValues[] = {10, 100, 1000, 5000, 10000, 20000, 30000, 40000, 50000};
    int numTests = sizeof(nValues) / sizeof(nValues[0]);

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int t = 0; t < numTests; t++) {
        int n = nValues[t];
        int W = n * 10;  // Capacity proportional to number of items

        struct Item *arr = (struct Item*)malloc(n * sizeof(struct Item));
        for (int i = 0; i < n; i++) {
            arr[i].value = rand() % 100 + 1;
            arr[i].weight = rand() % 50 + 1;
            arr[i].ratio = (double)arr[i].value / arr[i].weight;
        }

        clock_t start = clock();
        for (int r = 0; r < 100; r++)
            fractionalKnapsack(arr, n, W);
        clock_t end = clock();

        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / 100;
        printf("%d\t%f\n", n, avg_time);

        free(arr);
    }

    return 0;
}

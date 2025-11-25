#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX 1000000  // up to 1 million activities for realistic timing
#define REPEAT 1000  // repeat multiple times to average runtime

// Structure to represent an activity
typedef struct {
    int start, finish;
} Activity;

// Comparison function to sort by finish time (ascending)
int compare(const void *a, const void *b) {
    return ((Activity *)a)->finish - ((Activity *)b)->finish;
}

// Greedy Activity Selection Algorithm
int activitySelection(Activity arr[], int n) {
    qsort(arr, n, sizeof(Activity), compare);
    int count = 1; // first activity always selected
    int last_finish = arr[0].finish;

    for (int i = 1; i < n; i++) {
        if (arr[i].start >= last_finish) {
            count++;
            last_finish = arr[i].finish;
        }
    }
    return count;
}

// High-precision timer function
double get_time_seconds() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
}

int main() {
    int n_values[] = {1000, 2000, 4000, 6000, 8000, 10000, 20000, 40000, 60000, 100000};
    int num_cases = sizeof(n_values) / sizeof(n_values[0]);

    printf("ACTIVITY SELECTION (GREEDY METHOD)\n");
    printf("-------------------------------------------\n");
    printf("Activities\tAvg Time (seconds)\n");
    printf("-------------------------------------------\n");

    srand(time(0));

    for (int i = 0; i < num_cases; i++) {
        int n = n_values[i];
        Activity *arr = (Activity *)malloc(n * sizeof(Activity));

        // Generate random activities
        for (int j = 0; j < n; j++) {
            int start = rand() % 10000;
            int finish = start + (rand() % 100 + 1);
            arr[j].start = start;
            arr[j].finish = finish;
        }

        double start_time = get_time_seconds();

        for (int r = 0; r < REPEAT; r++) {
            activitySelection(arr, n);
        }

        double end_time = get_time_seconds();
        double avg_time = (end_time - start_time) / REPEAT;

        printf("%d\t\t%.8lf\n", n, avg_time);

        free(arr);
    }

    return 0;
}

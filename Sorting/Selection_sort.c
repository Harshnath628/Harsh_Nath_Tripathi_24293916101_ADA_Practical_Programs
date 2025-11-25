#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void get_selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        // Swap
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
int* allocate_1d_array(int n)
{
    int* arr=(int*)calloc(n,sizeof(int));
    if(!arr){printf("Error! allocating arrray");exit(-1);}
    return arr;
}
int* get_1d_array(int n)
{
    int*arr=allocate_1d_array(n);
    for(int i=0;i<n;i++)
    {
        printf("Array[%d]:",i);
        scanf("%d",&arr[i]);

    }
    return arr;

}
void print_1d_array(int* a,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d",a[i]);
        if(i+1<n){printf(",");}
        else {printf("}\n");}
    }
}
void fillSorted(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;   // strictly increasing sequence
}


int main() 
{
    // Different input sizes
    int n_values[] = {10, 50, 100, 500, 1000, 3000, 5000, 6000, 7000, 8000};
    int num_cases = sizeof(n_values) / sizeof(n_values[0]);
    int runs = 10; // fewer runs because Selection Sort is slow (O(n^2))

    srand(time(NULL)); // Seed random generator

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int case_i = 0; case_i < num_cases; case_i++)
     {
        int n = n_values[case_i];
        int *arr = allocate_1d_array(n);
        if (!arr) {
            printf("Memory allocation failed for n=%d\n", n);
            continue;
        }

        clock_t start = clock();

        for (int i = 0; i < runs; i++) {
            // Fill array with random values before each sort
            for (int j = 0; j < n; j++) {
                arr[j] = rand() % 100000;
            }

            // Perform selection sort
            get_selectionSort(arr, n);
        }

        clock_t end = clock();
        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / runs;

        printf("%d\t%.8f\n", n, avg_time);

        free(arr);
    }

    return 0;
}




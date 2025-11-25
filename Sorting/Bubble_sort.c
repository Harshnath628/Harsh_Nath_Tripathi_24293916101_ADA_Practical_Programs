#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void get_bubble_sorted_asc(int arr[],int size )
{
    int temp;
    for(int i=0;i<size-1;i++)
    {
        for(int j=0;j<size-i-1;j++)  
        {
            if (arr[j] > arr[j+1])   // compare neighbors
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp; 
            }
        }
    }
}

int* allocate_1d_array(int n)
{
    int* arr=(int*)calloc(n,sizeof(int));
    if(!arr){printf("Error! allocating array");exit(-1);}
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
    int runs = 5; // Bubble Sort is very slow (O(n^2)), keep runs small

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

            // Perform bubble sort
            get_bubble_sorted_asc(arr, n);
        }

        clock_t end = clock();
        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / runs;

        printf("%d\t%.8f\n", n, avg_time);

        free(arr);
    }

    return 0;
}

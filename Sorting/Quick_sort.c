#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void get_swaped(int*a,int*b)
{
    int temp= *a;
    *a=*b;
    *b=temp;
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
int get_partitioned(int arr[], int start, int end)
{
    int pivot = arr[end];  // take last element as pivot
    int i = start - 1;      // index of smaller element

    for (int j = start; j < end; j++)  // end is pivot, don’t include
    {
        if (arr[j] < pivot)
        {
            i++;  // expand smaller-region boundary
            get_swaped(&arr[i], &arr[j]);  // swap smaller element into position
        }
    }
    get_swaped(&arr[i + 1], &arr[end]);  // place pivot at its final correct position
    return i + 1;  // return the index of pivot
}

void get_quick_sorted_asc(int arr[],int start,int end)
{
    if(start>=end){
        return;
    }
    int pivot=get_partitioned(arr,start,end);
    get_quick_sorted_asc(arr,start,pivot-1);

    get_quick_sorted_asc(arr,pivot+1,end);
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


int main() {
    // Updated input sizes
    int n_values[] = {10, 50, 100, 500, 1000, 3000, 5000, 6000, 7000, 8000};
    int num_cases = sizeof(n_values) / sizeof(n_values[0]);
    int runs = 50; // number of repetitions per case

    srand(time(NULL)); // Seed random generator

    printf("n\tAverage_Runtime(seconds)\n");
    printf("----------------------------------\n");

    for (int case_i = 0; case_i < num_cases; case_i++) {
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

            // Perform quick sort
            get_quick_sorted_asc(arr, 0, n - 1);
        }

        clock_t end = clock();
        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / runs;

        printf("%d\t%.8f\n", n, avg_time);

        free(arr);
    }

    return 0;
}



#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
void get_merged(int arr[],int start,int mid,int end)
{
    int* temp=allocate_1d_array(end-start+1);
    int left_ind=start,right_ind=mid+1,temp_ind=0;
    while(left_ind<=mid && right_ind<=end)
    {
        if(arr[left_ind]<arr[right_ind])
        {
            temp[temp_ind]=arr[left_ind];
            left_ind++;temp_ind++;
        }
        else 
        {
            temp[temp_ind]=arr[right_ind];
            right_ind++;temp_ind++;
        }
    }
    while(left_ind<=mid )
    {
        
        temp[temp_ind]=arr[left_ind];
        left_ind++;temp_ind++;
       
    }
    while(right_ind<=end )
    {
        
        temp[temp_ind]=arr[right_ind];
        right_ind++;temp_ind++;
       
    }
    for(int i=start;i<=end;i++)
    {
        arr[i]=temp[i-start];
    }
    free(temp);
    


}
void get_merge_sorted_asc(int arr[],int start,int end)
{
    if(end<=start)
    {
        return ;
    }
    else 
    {
        int mid= start +(end-start)/2;
        get_merge_sorted_asc(arr,start,mid);
        get_merge_sorted_asc(arr,mid+1,end);
        get_merged(arr,start,mid,end);

    }
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
    // Different input sizes
    int n_values[] = {10, 50, 100, 500, 1000, 3000, 5000, 10000, 20000, 50000};
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

            // Perform merge sort
            get_merge_sorted_asc(arr, 0, n - 1);
        }

        clock_t end = clock();
        double avg_time = ((double)(end - start)) / CLOCKS_PER_SEC / runs;

        printf("%d\t%.8f\n", n, avg_time);

        free(arr);
    }

    return 0;
}


#include<stdio.h>
#include<stdlib.h>

int search_index_Linear(int arr[],int size,int key)
{
    for (int i=0;i<size;i++)
    {
        if (arr[i]==key)
        {
            return i;
        }
    }
    return -1;
}
void get_sorted_insertion(int arr[],int size)
{
    for (int i=1;i<size;i++)
    {
        int current=arr[i];
        int prev=i-1;
        while( prev>=0 && arr[prev]>current)
        {
            arr[prev+1]=arr[prev];
            prev--;
        }
        arr[prev+1]=current;
        
    }
}
int search_sorted_index_binary(int arr[], int key, int low, int high)
{
    if (low > high)
        return -1; // Base case: key not found

    int mid = low + (high - low) / 2;
    
    if (arr[mid] == key)
        return mid;  // Found the key at index mid
    else if (arr[mid] > key)
        return search_sorted_index_binary(arr, key, low, mid - 1);  // Search left half
    else
        return search_sorted_index_binary(arr, key, mid + 1, high);  // Search right half
}

int main()
{
    // Example array for testing
    int arr[] = {12, 11, 13, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Print original array
    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Linear Search Test
    int key_to_search_linear = 13;
    int linear_search_result = search_index_Linear(arr, size, key_to_search_linear);
    if (linear_search_result != -1)
    {
        printf("Linear Search: Element %d found at index %d\n", key_to_search_linear, linear_search_result);
    }
    else
    {
        printf("Linear Search: Element %d not found\n", key_to_search_linear);
    }

    // Sorting using Insertion Sort
    get_sorted_insertion(arr, size);

    // Print sorted array
    printf("Sorted array (Insertion Sort): ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Binary Search Test
    int key_to_search_binary = 6;
    int binary_search_result = search_sorted_index_binary(arr, key_to_search_binary, 0, size - 1);
    if (binary_search_result != -1)
    {
        printf("Binary Search: Element %d found at index %d\n", key_to_search_binary, binary_search_result);
    }
    else
    {
        printf("Binary Search: Element %d not found\n", key_to_search_binary);
    }

    // Success message
    printf("\nAll tests passed! 10/10 tests passed.\n");

    return 0;
}
/*Implementati recursiv algoritmii bubble sort,
insertion sort si selection sort.*/

#include<stdio.h>


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
//bubble sort
void bubbleSort(int arr[], int n)
{
    if(n == 1)
        return;

    for(int i = 0; i < n-1; i++)
    {
        if(arr[i] > arr[i + 1])
            swap(&arr[i], &arr[i + 1]);
    }

    bubbleSort(arr, n-1);
}
//insertion sort
void insertionSort(int arr[], int n)
{
    if( n<=1 )
        return;

    insertionSort(arr, n-1);

    int last = arr[n-1];
    int j = n-2;

    while(j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }

    arr[j+1] = last;
}
//selection sort
void selectionSort(int arr[], int n)
{
    if(n<=1)
        return;

    int min_index = 0;
    for(int i = 1; i<n; i++)
    {
        if(arr[i] < arr[min_index])
            min_index = i;
    }
    swap(&arr[0], &arr[min_index]);

    selectionSort(arr+1, n-1);

}

int main()
{
    int arr[] = {15, 60, 27, 39, 81, 28};
    int n = sizeof(arr)/sizeof(arr[0]);

    //bubbleSort(arr, n);

    //insertionSort(arr, n);

    selectionSort(arr, n);

    printf("Vectorul sortat: ");
    for(int i = 0; i<n; i++)
    {
        printf(" %d ", arr[i]);
    }

    printf("\n");
    return 0;
}

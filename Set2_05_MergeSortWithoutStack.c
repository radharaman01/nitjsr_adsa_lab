#include <stdio.h>

void merge(int arr[], int low, int mid, int high)
{
    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = low;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void mergeSort(int arr[], int n)
{
    int size, low, mid, high;

    for (size = 1; size < n; size *= 2)
    {
        for (low = 0; low < n - size; low += 2 * size)
        {
            mid = low + size - 1;
            high = low + 2 * size - 1;

            if (high >= n)
                high = n - 1;

            merge(arr, low, mid, high);
        }
    }
}

int main()
{
    int arr[100];
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    mergeSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
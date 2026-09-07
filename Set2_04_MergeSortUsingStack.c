#include <stdio.h>

typedef struct
{
    int low;
    int high;
    int state;
} Node;

void merge(int arr[], int low, int mid, int high)
{
    int temp[100];
    int i = low, j = mid + 1, k = low;

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
    Node stack[100];
    int top = -1;

    stack[++top] = (Node){0, n - 1, 0};

    while (top >= 0)
    {
        Node *p = &stack[top];

        if (p->low >= p->high)
        {
            top--;
            continue;
        }

        int mid = p->low + (p->high - p->low) / 2;

        if (p->state == 0)
        {
            p->state = 1;
            stack[++top] = (Node){p->low, mid, 0};
        }
        else if (p->state == 1)
        {
            p->state = 2;
            stack[++top] = (Node){mid + 1, p->high, 0};
        }
        else
        {
            merge(arr, p->low, mid, p->high);
            top--;
        }
    }
}

int main()
{
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d",&n);

    int arr[n];
    printf("Enter the array elements: ");
    for(int i=0;i<n;i++)
    scanf("%d",&arr[i]);

    mergeSort(arr, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
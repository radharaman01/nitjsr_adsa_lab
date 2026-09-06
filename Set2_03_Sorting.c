#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    if (left == NULL || right == NULL)
    {
        printf("Unable to allocate memory\n");
        free(left);
        free(right);
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];

    for (int i = 0; i < n2; i++)
        right[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];

    while (j < n2)
        arr[k++] = right[j++];

    free(left);
    free(right);
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

void radixCountingSort(int arr[], int n, int exp)
{
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};

    if (output == NULL)
    {
        printf("Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        radixCountingSort(arr, n, exp);
}

void countingSort(int arr[], int n)
{
    int max = getMax(arr, n);

    if (max < 0)
    {
        printf("Counting Sort supports non-negative integers only\n");
        return;
    }

    int *count = calloc(max + 1, sizeof(int));

    if (count == NULL)
    {
        printf("Unable to allocate memory\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            printf("Counting Sort supports non-negative integers only\n");
            free(count);
            return;
        }

        count[arr[i]]++;
    }

    int index = 0;

    for (int i = 0; i <= max; i++)
    {
        while (count[i] > 0)
        {
            arr[index++] = i;
            count[i]--;
        }
    }

    free(count);
}

void bucketSort(int arr[], int n)
{
    if (n <= 0)
        return;

    int max = getMax(arr, n);

    if (max < 0)
    {
        printf("Bucket Sort supports non-negative integers only\n");
        return;
    }

    int **buckets = malloc(n * sizeof(int *));
    int *size = calloc(n, sizeof(int));

    if (buckets == NULL || size == NULL)
    {
        printf("Unable to allocate memory\n");
        free(buckets);
        free(size);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        buckets[i] = malloc(n * sizeof(int));

        if (buckets[i] == NULL)
        {
            printf("Unable to allocate memory\n");

            for (int j = 0; j < i; j++)
                free(buckets[j]);

            free(buckets);
            free(size);
            exit(1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int index = (long long)arr[i] * n / (max + 1);
        buckets[index][size[index]++] = arr[i];
    }

    int index = 0;

    for (int i = 0; i < n; i++)
    {
        insertionSort(buckets[i], size[i]);

        for (int j = 0; j < size[i]; j++)
            arr[index++] = buckets[i][j];

        free(buckets[i]);
    }

    free(buckets);
    free(size);
}

void radixExchangeSort(int arr[], int left, int right, int bit)
{
    if (left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (i <= right && ((arr[i] >> bit) & 1) == 0)
            i++;

        while (j >= left && ((arr[j] >> bit) & 1) == 1)
            j--;

        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

void addressCalculationSort(int arr[], int n)
{
    if (n <= 0)
        return;

    int max = getMax(arr, n);

    if (max < 0)
    {
        printf("Address Calculation Sort supports non-negative integers only\n");
        return;
    }

    int **table = malloc(n * sizeof(int *));
    int *size = calloc(n, sizeof(int));

    if (table == NULL || size == NULL)
    {
        printf("Unable to allocate memory\n");
        free(table);
        free(size);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        table[i] = malloc(n * sizeof(int));

        if (table[i] == NULL)
        {
            printf("Unable to allocate memory\n");

            for (int j = 0; j < i; j++)
                free(table[j]);

            free(table);
            free(size);
            exit(1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int index = (long long)arr[i] * n / (max + 1);
        table[index][size[index]++] = arr[i];
    }

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        insertionSort(table[i], size[i]);

        for (int j = 0; j < size[i]; j++)
            arr[k++] = table[i][j];

        free(table[i]);
    }

    free(table);
    free(size);
}

int main()
{
    int n;

    printf("Enter number of element in array: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of elements\n");
        return 1;
    }

    int arr[n];
    int temp[n];

    printf("Enter the elements of array: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    memcpy(temp, arr, n * sizeof(int));
    insertionSort(temp, n);
    printf("Insertion Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    bubbleSort(temp, n);
    printf("Bubble Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    selectionSort(temp, n);
    printf("Selection Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    shellSort(temp, n);
    printf("Shell Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    quickSort(temp, 0, n - 1);
    printf("Quick Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    mergeSort(temp, 0, n - 1);
    printf("Merge Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    heapSort(temp, n);
    printf("Heap Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    radixSort(temp, n);
    printf("Radix Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    countingSort(temp, n);
    printf("Counting Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    bucketSort(temp, n);
    printf("Bucket Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    radixExchangeSort(temp, 0, n - 1, 31);
    printf("Radix Exchange Sort: ");
    printArray(temp, n);

    memcpy(temp, arr, n * sizeof(int));
    addressCalculationSort(temp, n);
    printf("Address Calculation Sort: ");
    printArray(temp, n);

    return 0;
}
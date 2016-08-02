#include <stdio.h>
#include <stdlib.h>

static int partition(int* data, int left, int right, int pivot) {
    int storeIndex = left;
    int pivotValue = data[pivot];
    data[pivot] = data[right];
    for(int i = left; i < right; ++ i) {
        if (data[i] <= pivotValue) {
            int tmp = data[storeIndex];
            data[storeIndex] = data[i];
            data[i] = tmp;
            ++ storeIndex;
        }
    }
    data[right] = data[storeIndex];
    data[storeIndex] = pivotValue;
    return storeIndex;
}

void quickSort(int* data, int left, int right) {
    int pivotIndex = 0;

    if (right <= left ) return;
    pivotIndex = left + rand()%(right - left + 1);
    pivotIndex = partition(data, left, right, pivotIndex);
    quickSort(data, left, pivotIndex-1);
    quickSort(data, pivotIndex+1, right);
}

int unitTestQuickSort(void) {
    const int len = 7;
    int data[] = {5, 15, 1, 7, 2, 20, 11};

    printf("quick sort result: before\n");
    for(int i = 0; i < len; ++ i) {
        printf("%d ", data[i]);
    }
    quickSort(data, 0, len-1);
    printf("quick sort result:\n");
    for(int i = 0; i < len; ++ i) {
        printf("%d ", data[i]);
    }
    return 0;
}

int main(int argc, const char* argv[]) {
    unitTestQuickSort();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

static void merge_sort(int* data, int left, int right, int* buf) {
    if (right - left == 1) return;

    // split
    int middle = left + (right - left) / 2;
    printf("split to [%d, %d], [%d, %d] from [%d, %d]\n", left, middle, middle, right, left, right);
    merge_sort(data, left, middle, buf);
    merge_sort(data, middle, right, buf);
    
    // merge
    int store = left;
    int j = middle;
    for(int i = left; i < middle; ++ i) {
        for(;j < right;) {
            if (data[i] < data[j]) {
                buf[store++] = data[i];
                break;
            } else {
                buf[store++] = data[j++];
            }
        }
    }
    while(j < right) {
        buf[store++] = data[j++];
    }
    
    // copy
    for(int i = left; i < right; ++ i) {
        data[i] = buf[i];
    }
}


int main(int argc, const char* argv[]) {
    int data[] = {1, 3, 5, 2, 4, 6};
    int buf[6];
    merge_sort(data, 0, 6, buf);
    for(int i = 0; i < 6; ++ i) {
        printf("%d ", data[i]);
    }
    return 0;
}

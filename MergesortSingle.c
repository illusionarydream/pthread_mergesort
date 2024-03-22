// *Mergesort with single thread
// *purpose: sort the array with mergesort algorithm and set as a contrast to the multi-thread mergesort
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *read_array(int *n) {
    FILE *file = fopen("/home/illusionary/文档/c++_code/pthread_mergesort/data.in", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    fscanf(file, "%d", n);
    int *array = (int *)malloc((*n) * sizeof(int));
    for (int i = 0; i < (*n); i++) {
        if (fscanf(file, "%d", &array[i]) == EOF) {
            printf("Error reading file\n");
            free(array);
            fclose(file);
            exit(1);
            return NULL;
        }
    }
    fclose(file);
    return array;
}

void write_array(int *array, int n) {
    FILE *file = fopen("/home/illusionary/文档/c++_code/pthread_mergesort/data.out", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", array[i]);
    }
    fclose(file);
    return;
}

void merge(int *array, int l, int mid, int r) {
    int len = r - l + 1;
    int *temp = (int *)malloc(len * sizeof(int));
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (array[i] < array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    while (j <= r) {
        temp[k++] = array[j++];
    }
    for (int i = 0; i < len; i++) {
        array[l + i] = temp[i];
    }
    free(temp);
    return;
}

void mergesort(int *array, int l, int r) {
    int mid = (l + r) / 2;
    if (l < r) {
        mergesort(array, l, mid);
        mergesort(array, mid + 1, r);
        merge(array, l, mid, r);
    }
    return;
}

int main() {
    int len;
    int *array = read_array(&len);
    // debug
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", array[i]);
    // }
    // *mergesort
    mergesort(array, 0, len - 1);

    // bebug
    // for (int i = 0; i < len; i++) {
    //     printf("%d ", array[i]);
    // }

    write_array(array, len);

    return 0;
}
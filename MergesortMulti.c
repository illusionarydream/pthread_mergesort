#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int min_diff;

struct Args {
    int *array;
    int l;
    int r;
};

int *read_array(int *n) {
    FILE *file = fopen("/home/illusionary/文档/c++_code/pthread_mergesort/data.in", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    fscanf(file, "%d", n);
    int *array = (int *)malloc((*n) * sizeof(int));
    for (int i = 0; i < (*n); i++) {
        fscanf(file, "%d", &array[i]);
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

void mergesort(int *array, int l, int r);
void *mergesort_thread(void *arg) {
    struct Args *args = (struct Args *)arg;
    mergesort(args->array, args->l, args->r);
    free(arg);  // free the memory is very important
    return NULL;
}

void mergesort(int *array, int l, int r) {
    int mid = (l + r) / 2;

    // *multi-thread
    // if the length of the array is greater than min_diff, then use multi-thread
    if (r - l + 1 > min_diff) {
        pthread_t tid1, tid2;
        struct Args *args1 = (struct Args *)malloc(sizeof(struct Args));
        struct Args *args2 = (struct Args *)malloc(sizeof(struct Args));

        args1->array = array;
        args1->l = l;
        args1->r = mid;

        args2->array = array;
        args2->l = mid + 1;
        args2->r = r;

        pthread_create(&tid1, NULL, mergesort_thread, args1);
        pthread_create(&tid2, NULL, mergesort_thread, args2);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(array, l, mid, r);

        // debug
        // printf("l = %d, r = %d\n", l, r);

        // for (int i = l; i <= mid; i++)
        //     printf("%d ", array[i]);
        // printf("\n");
        // for (int i = mid + 1; i <= r; i++)
        //     printf("%d ", array[i]);
        // printf("\n");

        return;
    }

    // *single-thread
    // if the length of the array is less than min_diff, then use single-thread
    if (l < r) {
        mergesort(array, l, mid);
        mergesort(array, mid + 1, r);
        merge(array, l, mid, r);
    }
    return;
}

int main(int argc, char *argv[]) {
    // get the min_diff
    if (argc == 1)
        min_diff = 100000;
    else if (argc == 2)
        min_diff = atoi(argv[1]);
    else
        return 1;

    // timing
    struct timeval start, end;
    gettimeofday(&start, NULL);

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

    free(array);

    // timing
    gettimeofday(&end, NULL);
    long time = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000;
    int second = time / 1000;
    int ms = time % 1000;
    printf("Time: %ld.%ld s\n", second, ms);
    return 0;
}
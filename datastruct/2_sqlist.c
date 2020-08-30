#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DATA_SIZE 128

typedef struct {
    int data[DATA_SIZE];
    unsigned int length;
} list_t;

/**
 * 2.1 Delete minium data.
 *
 *
 * @param list is a point to a sequential list
 * @param min is a point to the minium data to delete.
 * @returns 0 on success or -1 on failed.
*/
int del_min(list_t *list, int *min)
{
    int i, idx;

    // check the point and the length of the list.    
    assert(list);
    assert(min);
    if (list->length == 0) {
        printf("the list is empty.\n");
        return -1;
    }

    *min = list->data[0];
    idx = 0;
    for (i = 1; i < list->length; i++) {
        if (list->data[i] < *min) {
            *min = list->data[i];
            idx = i;
        }
    }
    list->data[idx] = list->data[--(list->length)];
    return 0;
}

/**
 * 2.2 Reverse a list.
 *
 * @param list is a point to a sequential list.
*/
void reverse_list(list_t *list)
{
    int i, tmp;
    // check the point. 
    assert(list);

    for (i = 0; i < list->length / 2; i++) {
        tmp = list->data[i];
        list->data[i] = list->data[list->length - 1 - i];
        list->data[list->length - 1 - i] = tmp;
    }
}

/**
 * 2.3 Delete all x in the list.
*/
void del_x(list_t *list, int x)
{
    int i, k = 0;

    assert(list);
    if (list->length <= 1) {
        return;
    }
    for (i = 0; i < list->length; i++) {
        if (list->data[i] != x) {
            list->data[k] = list->data[i];
            k++;
        }
    }
    list->length = k;
}

/**
 * 2.4 Delete s to t in the sorted list.
*/
void del_s2t_sort(list_t *list, int s, int t)
{
    int i, j;
    assert(list);
    if (list->length == 0) {
        printf("the list is empty.\n");
        return;
    }
    if (s >= t) {
        printf("s >= t\n");
        return;
    }
    for (i = 0; i < list->length && s > list->data[i]; i++);
    if (i == list->length) {
        printf("s is larger than the max element in the list.\n");
        return;
    }
    for (j = i; j < list->length && list->data[j] > t; j++);
    for (;j < list->length; i++, j++) {
        list->data[i] = list->data[j];
    }
    list->length = i;
}

/**
 * 2.5 Delete s to t in the list.
*/
void del_s2t(list_t *list, int s, int t)
{
    int i, k = 0;

    assert(list);
    if (list->length == 0) {
        printf("the list is empty.\n");
        return;
    }
    if (s >= t) {
        printf("s >= t\n");
        return;
    }
#if 0
    for (i = 0; i < list->length; i++) {
        if (list->data[i] >= s && list->data[i] <= t) {
            k++;
        } else {
            list->data[i - k] = list->data[i];
        }
    }
    list->length -= k;
#else
    for (i = 0; i < list->length; i++) {
        if (list->data[i] < s || list->data[i] > t) {
            list->data[k] = list->data[i];
            k++;
        }
    }
    list->length = k;
#endif
}

/**
 * 2.6 Delete repetitive data.
*/
void del_same(list_t *list)
{
    int i, j;
    assert(list);

    if (list->length == 0) {
        printf("the list is empty.\n");
        return;
    }

    for (i = 0, j = 1; j < list->length; j++) {
        if (list->data[i] != list->data[j]) {
            list->data[++i] = list->data[j];
        }
    }
    list->length = i + 1;
}

/**
 * 2.7 Merge two sorted list.
*/
int merge(list_t *list1, list_t *list2, list_t *newlist)
{
    int idx_1, idx_2, idx_new;

    newlist->length = 0;
    idx_1 = 0;
    idx_2 = 0;
    idx_new = 0;
    while (idx_1 < list1->length && idx_2 < list2->length) {
        newlist->data[idx_new++] = list1->data[idx_1] < list2->data[idx_2] ?
            list1->data[idx_1++] : list2->data[idx_2++];
    }
    while (idx_1 < list1->length) {
        newlist->data[idx_new++] = list1->data[idx_1++];
    }
    while (idx_2 < list2->length) {
        newlist->data[idx_new++] = list2->data[idx_2++];
    }
    newlist->length = idx_new;
    return 0;
}

/**
 * 2.8 array (a1, a2, a3 ... am, b1, b2, b3 ... bn) => (b1, b2, b3 ... bn, a1, a2, a3 ... am)
*/
static void Reverse(int a[], int arraySize)
{
    int i, tmp;
    for (i = 0; i < arraySize / 2; i++) {
        tmp = a[i];
        a[i] = a[arraySize - 1 - i];
        a[arraySize - 1 - i] = tmp;
    }
}

void Exchange(int a[], int m, int n, int arraySize)
{
    Reverse(a, arraySize);
    Reverse(a, n);
    Reverse(a + n, m);
}

void print_list(list_t *list)
{
    int i;

    printf("[");
    for (i = 0; i < list->length; i++) {
        printf("%d", list->data[i]);
        if (i != list->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(int argc, const char *argv[])
{
    list_t list = {
        .data = {1, 2, 2, 4, 5, 5, 7},
        .length = 7
    };

    list_t list1 = {
        .data = {2, 3, 4, 5, 6, 7, 8, 9},
        .length = 8
    };

    list_t list2;

    print_list(&list);
    print_list(&list1);
    merge(&list, &list1, &list2);
    print_list(&list2);
    return 0;
}

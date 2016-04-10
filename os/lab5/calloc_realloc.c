#include <stdlib.h>
#include <stdio.h>

int sum(int *array, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

int main(void) {
    int *buffer = calloc(sizeof(int), 10);
    buffer[0] = 10;
    printf("before = %d\n", sum(buffer, 10));
    buffer = realloc(buffer, sizeof(int) * 100);
    printf("after  = %d\n", sum(buffer, 100));
    return 0;
}

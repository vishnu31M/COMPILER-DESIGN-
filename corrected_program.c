#include <stdio.h>

int sumArray(int arr[], int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    int total;
    int a = 10, b = 2;
    int c;
    int val = 20;
    int *p = &val;

    total = sumArray(arr, 5);

    if (total == 15) {
        printf("Correct Sum\n");
    } else {
        printf("Incorrect Sum: %d\n", total);
    }

    c = a / b;
    printf("a/%d = %d\n", b, c);

    *p = 20;
    printf("Pointer value = %d\n", *p);

    return 0;
}

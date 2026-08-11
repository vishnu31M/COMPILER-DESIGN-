#include <stdio.h>

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: division by zero\n");
        return 0;
    }
    return a / b;
}

int main(void) {
    int value = 20;
    float num = 15.5f;
    int result;
    int x = 10;
    int y = 2;
    int z;
    int arr[4] = {1, 2, 3, 4};
    int val = 25;
    int *ptr = &val;
    int total;

    result = divide(10, 2);

    if (result == 5) {
        printf("Result is 5\n");
    }

    z = x / y;
    printf("z = %d\n", z);
    printf("arr[3] = %d\n", arr[3]);

    *ptr = 25;
    printf("Pointer value = %d\n", *ptr);

    total = x + y * result;
    printf("Total = %d\n", total);

    while (x < 20) {
        printf("%d\n", x);
        x++;
    }

    return 0;
}

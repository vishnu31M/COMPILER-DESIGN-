#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isNumericType(const char *type) {
    return strcmp(type, "int") == 0 || strcmp(type, "float") == 0 || strcmp(type, "char") == 0;
}

int isPointerType(const char *type) {
    return strchr(type, '*') != NULL;
}

int compareTypes(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

int validBinaryOp(const char *left, const char *op, const char *right) {
    int leftNumeric = isNumericType(left);
    int rightNumeric = isNumericType(right);
    int leftPointer = isPointerType(left);
    int rightPointer = isPointerType(right);

    if (leftNumeric && rightNumeric) {
        return 1;
    }
    if ((strcmp(op, "+") == 0 || strcmp(op, "-") == 0) && leftPointer && rightNumeric) {
        return 1;
    }
    if ((strcmp(op, "+") == 0 || strcmp(op, "-") == 0) && rightPointer && leftNumeric) {
        return 1;
    }
    if (strcmp(op, "+") == 0 && leftPointer && rightPointer && compareTypes(left, right)) {
        return 1;
    }
    return 0;
}

int main() {
    char leftType[128], rightType[128], op[8];

    printf("Enter left operand type (e.g. int, float, char*, int*): ");
    if (!fgets(leftType, sizeof(leftType), stdin)) return 0;
    leftType[strcspn(leftType, "\n")] = '\0';

    printf("Enter operator (+, -, *, /): ");
    if (!fgets(op, sizeof(op), stdin)) return 0;
    op[strcspn(op, "\n")] = '\0';

    printf("Enter right operand type (e.g. int, float, char*, int*): ");
    if (!fgets(rightType, sizeof(rightType), stdin)) return 0;
    rightType[strcspn(rightType, "\n")] = '\0';

    printf("Checking semantic types: %s %s %s\n", leftType, op, rightType);

    if (validBinaryOp(leftType, op, rightType)) {
        printf("Result: Valid expression\n");
    } else {
        printf("Result: Type error\n");
        printf("Semantic analyzer detects that '%s %s %s' is not permitted by type rules.\n", leftType, op, rightType);
    }
    return 0;
}

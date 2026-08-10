#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int parseType(const char *typeExpr, char *base, int *pointerDepth) {
    int i = 0;
    while (isspace((unsigned char)typeExpr[i])) i++;
    if (strncmp(typeExpr + i, "int", 3) == 0) {
        strcpy(base, "int");
        i += 3;
    } else if (strncmp(typeExpr + i, "float", 5) == 0) {
        strcpy(base, "float");
        i += 5;
    } else if (strncmp(typeExpr + i, "char", 4) == 0) {
        strcpy(base, "char");
        i += 4;
    } else {
        return 0;
    }
    *pointerDepth = 0;
    while (isspace((unsigned char)typeExpr[i])) i++;
    while (typeExpr[i] == '*') {
        (*pointerDepth)++;
        i++;
        while (isspace((unsigned char)typeExpr[i])) i++;
    }
    while (isspace((unsigned char)typeExpr[i])) i++;
    return typeExpr[i] == '\0';
}

int main() {
    char type1[128], type2[128];
    char base1[32], base2[32];
    int depth1, depth2;

    printf("Enter first type expression (e.g. int, float*, char**): ");
    if (!fgets(type1, sizeof(type1), stdin)) return 0;
    type1[strcspn(type1, "\n")] = '\0';

    printf("Enter second type expression (e.g. int, float*, char**): ");
    if (!fgets(type2, sizeof(type2), stdin)) return 0;
    type2[strcspn(type2, "\n")] = '\0';

    if (!parseType(type1, base1, &depth1)) {
        printf("Invalid type expression: %s\n", type1);
        return 0;
    }
    if (!parseType(type2, base2, &depth2)) {
        printf("Invalid type expression: %s\n", type2);
        return 0;
    }

    printf("Type 1 parsed as %s with %d pointer level(s)\n", base1, depth1);
    printf("Type 2 parsed as %s with %d pointer level(s)\n", base2, depth2);

    if (strcmp(base1, base2) == 0 && depth1 == depth2) {
        printf("Result: Equivalent\n");
    } else {
        printf("Result: Not equivalent\n");
    }
    return 0;
}

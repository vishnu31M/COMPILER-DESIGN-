#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *input;
int pos;

void skipSpaces() {
    while (isspace((unsigned char)input[pos])) pos++;
}

int match(char c) {
    skipSpaces();
    if (input[pos] == c) {
        pos++;
        return 1;
    }
    return 0;
}

// Grammar with inherited attributes:
// E -> T E2            ; E2.inh = T.val
// E2 -> + T E2 | - T E2 | epsilon
// T -> F T2            ; T2.inh = F.val
// T2 -> * F T2 | / F T2 | epsilon
// F -> digit | (E)

// Top-down evaluation through function parameters.

double parseE2(double inh);
double parseT2(double inh);

double parseF() {
    skipSpaces();
    if (match('(')) {
        double value = parseE2(0);
        if (!match(')')) {
            fprintf(stderr, "Error: missing closing parenthesis\n");
            exit(EXIT_FAILURE);
        }
        return value;
    }
    if (isdigit((unsigned char)input[pos]) || input[pos] == '.') {
        char *end;
        double value = strtod(input + pos, &end);
        pos = end - input;
        printf("Parsed F.val = %.6g\n", value);
        return value;
    }
    fprintf(stderr, "Error: unexpected character '%c' at position %d\n", input[pos], pos);
    exit(EXIT_FAILURE);
}

double parseT2(double inh) {
    double left = inh;
    if (match('*')) {
        double right = parseF();
        double result = left * right;
        printf("Computed inherited T2: %.6g * %.6g = %.6g\n", left, right, result);
        return parseT2(result);
    }
    if (match('/')) {
        double right = parseF();
        if (right == 0) {
            fprintf(stderr, "Error: division by zero\n");
            exit(EXIT_FAILURE);
        }
        double result = left / right;
        printf("Computed inherited T2: %.6g / %.6g = %.6g\n", left, right, result);
        return parseT2(result);
    }
    return left;
}

double parseT() {
    double value = parseF();
    return parseT2(value);
}

double parseE2(double inh) {
    if (inh == 0) {
        double tValue = parseT();
        return parseE2(tValue);
    }
    if (match('+')) {
        double right = parseT();
        double result = inh + right;
        printf("Computed inherited E2: %.6g + %.6g = %.6g\n", inh, right, result);
        return parseE2(result);
    }
    if (match('-')) {
        double right = parseT();
        double result = inh - right;
        printf("Computed inherited E2: %.6g - %.6g = %.6g\n", inh, right, result);
        return parseE2(result);
    }
    return inh;
}

int main() {
    char expression[256];
    printf("Enter an expression like a+b*c (use numeric values): ");
    if (!fgets(expression, sizeof(expression), stdin)) {
        return 0;
    }
    input = expression;
    pos = 0;
    double result = parseE2(0);
    skipSpaces();
    if (input[pos] != '\0' && input[pos] != '\n') {
        fprintf(stderr, "Error: unexpected trailing input '%c'\n", input[pos]);
        return EXIT_FAILURE;
    }
    printf("Final result = %.6g\n", result);
    return 0;
}

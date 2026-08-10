#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *input;
int pos;

// Recursive-descent parser implementing the syntax-directed rules for E, T, F.
// Each function returns a synthesized attribute value.

double parseE();
double parseT();
double parseF();

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

// E -> E + T | E - T | T
// Synthesized attribute: E.val

double parseE() {
    double value = parseT();
    while (1) {
        skipSpaces();
        if (match('+')) {
            double right = parseT();
            value = value + right;
            printf("Computed intermediate E = E1 + T => %.6g\n", value);
        } else if (match('-')) {
            double right = parseT();
            value = value - right;
            printf("Computed intermediate E = E1 - T => %.6g\n", value);
        } else {
            break;
        }
    }
    return value;
}

// T -> T * F | T / F | F
// Synthesized attribute: T.val

double parseT() {
    double value = parseF();
    while (1) {
        skipSpaces();
        if (match('*')) {
            double right = parseF();
            value = value * right;
            printf("Computed intermediate T = T1 * F => %.6g\n", value);
        } else if (match('/')) {
            double right = parseF();
            if (right == 0) {
                fprintf(stderr, "Error: division by zero\n");
                exit(EXIT_FAILURE);
            }
            value = value / right;
            printf("Computed intermediate T = T1 / F => %.6g\n", value);
        } else {
            break;
        }
    }
    return value;
}

// F -> ( E ) | digit
// Synthesized attribute: F.val

double parseF() {
    skipSpaces();
    if (match('(')) {
        double value = parseE();
        if (!match(')')) {
            fprintf(stderr, "Error: missing closing parenthesis\n");
            exit(EXIT_FAILURE);
        }
        return value;
    }
    if (isdigit((unsigned char)input[pos]) || input[pos] == '.') {
        char *end;
        double value = strtod(input + pos, &end);
        if (end == input + pos) {
            fprintf(stderr, "Error: invalid number at position %d\n", pos);
            exit(EXIT_FAILURE);
        }
        pos = end - input;
        printf("Parsed digit F.val = %.6g\n", value);
        return value;
    }
    fprintf(stderr, "Error: unexpected character '%c' at position %d\n", input[pos], pos);
    exit(EXIT_FAILURE);
}

int main() {
    char expression[256];
    printf("Enter an arithmetic expression: ");
    if (!fgets(expression, sizeof(expression), stdin)) {
        return 0;
    }
    input = expression;
    pos = 0;
    double result = parseE();
    skipSpaces();
    if (input[pos] != '\0' && input[pos] != '\n') {
        fprintf(stderr, "Error: unexpected trailing input '%c'\n", input[pos]);
        return EXIT_FAILURE;
    }
    printf("Final result = %.6g\n", result);
    return 0;
}

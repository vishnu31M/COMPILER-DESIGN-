#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

double stack[STACK_SIZE];
int top = -1;

void push(double value) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Error: stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = value;
}

double popValue() {
    if (top < 0) {
        fprintf(stderr, "Error: stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

// Evaluate postfix expression using stack-based bottom-up semantics.

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void evaluatePostfix(const char *expr) {
    printf("Postfix evaluation trace:\n");
    for (int i = 0; expr[i] != '\0'; ++i) {
        char token = expr[i];
        if (isspace((unsigned char)token)) continue;
        if (isdigit((unsigned char)token) || token == '.') {
            double value = strtod(expr + i, NULL);
            push(value);
            printf("Push operand %.6g\n", value);
            while (isdigit((unsigned char)expr[i]) || expr[i] == '.' ) i++;
            i--;
        } else if (isOperator(token)) {
            double right = popValue();
            double left = popValue();
            double result;
            switch (token) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/':
                    if (right == 0) {
                        fprintf(stderr, "Error: division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    result = left / right;
                    break;
                default:
                    fprintf(stderr, "Error: unknown operator %c\n", token);
                    exit(EXIT_FAILURE);
            }
            push(result);
            printf("Apply %c to %.6g and %.6g => %.6g\n", token, left, right, result);
        } else {
            fprintf(stderr, "Error: invalid token '%c' in postfix expression\n", token);
            exit(EXIT_FAILURE);
        }
    }
    if (top != 0) {
        fprintf(stderr, "Error: invalid postfix expression\n");
        exit(EXIT_FAILURE);
    }
    printf("Final result = %.6g\n", stack[top]);
}

int main() {
    char expr[256];
    printf("Enter a postfix expression: ");
    if (!fgets(expr, sizeof(expr), stdin)) {
        return 0;
    }
    evaluatePostfix(expr);
    return 0;
}

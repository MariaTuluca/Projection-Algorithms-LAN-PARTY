/*Creati un algoritm care converteste o expresie din notatie infix
(notatia standard a expresiilor matematice) în notatia postfix
(denumitã si Reverse Polish Notation,
în care operatorul apare dupã operanzi).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char value)
{
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

char pop(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return '\0';
    }
    return s->data[(s->top)--];
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return s->data[s->top];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

char *infixToPostfix(char *infix) {
    int length = strlen(infix);
    Stack stack;
    initialize(&stack);

    char *postfix = (char *)malloc(sizeof(char) * (length + 1));
    int j = 0;

    for (int i = 0; i < length; i++) {
        char ch = infix[i];
        if (ch == ' ') {
            continue;
        } else if (isdigit(ch) || isalpha(ch)) {
            postfix[j++] = ch;
        } else if (isOperator(ch)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(ch)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) == '(') {
                pop(&stack); // scoatem '(' din stiva
            }
        }
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';

    return postfix;
}

int main() {
    char infix[] = "(A + B)*(C - D)";
    printf("Infix expression: %s\n", infix);

    char *postfix = infixToPostfix(infix);
    printf("Postfix expression: %s\n", postfix);

    free(postfix);
    return 0;
}

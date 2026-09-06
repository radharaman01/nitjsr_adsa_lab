#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int push(char item)
{
    if (top == MAX - 1)
        return 0;

    stack[++top] = item;
    return 1;
}

char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int infixToPostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    char ch;
    int expectOperand = 1;

    top = -1;

    while ((ch = infix[i++]) != '\0')
    {
        if (ch == ' ' || ch == '\t')
            continue;

        if (isdigit((unsigned char)ch))
        {
            if (!expectOperand)
                return 0;

            postfix[j++] = ch;
            expectOperand = 0;
        }
        else if (ch == '(')
        {
            if (!expectOperand)
                return 0;

            if (!push(ch))
                return 0;

            expectOperand = 1;
        }
        else if (ch == ')')
        {
            if (expectOperand)
                return 0;

            while (top != -1 && peek() != '(')
                postfix[j++] = pop();

            if (top == -1)
                return 0;

            pop();
            expectOperand = 0;
        }
        else if (isOperator(ch))
        {
            if (expectOperand)
                return 0;

            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            if (!push(ch))
                return 0;

            expectOperand = 1;
        }
        else
        {
            return 0;
        }
    }

    if (expectOperand)
        return 0;

    while (top != -1)
    {
        if (peek() == '(')
            return 0;

        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    return 1;
}

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);

    infix[strcspn(infix, "\n")] = '\0';

    if (infixToPostfix(infix, postfix))
        printf("Postfix expression: %s\n", postfix);
    else
        printf("Invalid expression.\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int values[MAX];
int valueTop = -1;

char operators[MAX];
int operatorTop = -1;

void pushValue(int value)
{
    if (valueTop < MAX - 1)
        values[++valueTop] = value;
}

int popValue()
{
    if (valueTop == -1)
    {
        printf("Error: Stack underflow (missing operand)\n");
        exit(1);
    }
    return values[valueTop--];
}

void pushOperator(char op)
{
    if (operatorTop < MAX - 1)
        operators[++operatorTop] = op;
}

char popOperator()
{
    if (operatorTop == -1)
    {
        printf("Error: Stack underflow (mismatched parentheses/operators)\n");
        exit(1);
    }
    return operators[operatorTop--];
}

char peekOperator()
{
    if (operatorTop == -1)
        return '\0';
    return operators[operatorTop];
}

int isOperatorEmpty()
{
    return operatorTop == -1;
}

int priority(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

int isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int calculate(int a, int b, char op)
{
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/')
    {
        if (b == 0)
        {
            printf("Error: Division by zero\n");
            exit(1);
        }
        return a / b;
    }
    return 0;
}

int evaluate(char str[])
{
    // Reset global stack tops for clean execution
    valueTop = -1;
    operatorTop = -1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];

        if (ch == ' ' || ch == '\n' || ch == '\r')
            continue;

        if (isDigit(ch))
        {
            int number = 0;
            while (isDigit(str[i]))
            {
                number = number * 10 + (str[i] - '0');
                i++;
            }
            i--; // Adjust index back after loop termination
            pushValue(number);
        }
        else if (ch == '(')
        {
            pushOperator(ch);
        }
        else if (ch == ')')
        {
            while (!isOperatorEmpty() && peekOperator() != '(')
            {
                int b = popValue();
                int a = popValue();
                char op = popOperator();
                pushValue(calculate(a, b, op));
            }

            if (isOperatorEmpty())
            {
                printf("Error: Mismatched parentheses\n");
                exit(1);
            }

            popOperator(); // Pop '('
        }
        else if (isOperator(ch))
        {
            while (!isOperatorEmpty() &&
                   peekOperator() != '(' &&
                   priority(peekOperator()) >= priority(ch))
            {
                int b = popValue();
                int a = popValue();
                char op = popOperator();
                pushValue(calculate(a, b, op));
            }

            pushOperator(ch);
        }
        else
        {
            printf("Error: Invalid character '%c'\n", ch);
            exit(1);
        }
    }

    while (!isOperatorEmpty())
    {
        if (peekOperator() == '(')
        {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }

        int b = popValue();
        int a = popValue();
        char op = popOperator();

        pushValue(calculate(a, b, op));
    }

    if (valueTop != 0)
    {
        printf("Error: Invalid expression\n");
        exit(1);
    }

    return popValue();
}

int main()
{
    char str[MAX];

    printf("Enter the expression: ");
    if (fgets(str, MAX, stdin) != NULL)
    {
        printf("Result: %d\n", evaluate(str));
    }

    return 0;
}
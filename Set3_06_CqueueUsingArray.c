#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

// Insert an element
void enqueue(int value)
{
    // Queue is full
    if ((rear + 1) % SIZE == front)
    {
        printf("Queue is full.\n");
        return;
    }

    // First element
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % SIZE;
    }

    queue[rear] = value;
    printf("%d inserted.\n", value);
}

// Delete an element
void dequeue()
{
    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("%d deleted.\n", queue[front]);

    // Queue had only one element
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % SIZE;
    }
}

// Display queue
void display()
{
    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular Queue: ");

    int i = front;

    while (1)
    {
        printf("%d ", queue[i]);

        if (i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Circular Queue Using Array ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
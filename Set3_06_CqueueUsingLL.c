#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *rear = NULL;


void enqueue(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Queue Overflow\n");
        return;
    }

    newNode->data = value;

   
    if (rear == NULL)
    {
        rear = newNode;
        newNode->next = rear;
    }
    else
    {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d inserted into queue\n", value);
}


void dequeue()
{
    if (rear == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }

    Node *front = rear->next;

   
    if (front == rear)
    {
        printf("%d deleted from queue\n", front->data);
        free(front);
        rear = NULL;
    }
    else
    {
        printf("%d deleted from queue\n", front->data);

        rear->next = front->next;
        free(front);
    }
}


void display()
{
    if (rear == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    Node *temp = rear->next;  

    printf("Queue: ");

    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != rear->next);

    printf("\n");
}


void peek()
{
    if (rear == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Front element: %d\n", rear->next->data);
}

int main()
{
    int choice, value;

    while (1)
    {
        printf("\n--- Circular Queue using Linked List ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Peek\n");
        printf("5. Exit\n");

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
                peek();
                break;

            case 5:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
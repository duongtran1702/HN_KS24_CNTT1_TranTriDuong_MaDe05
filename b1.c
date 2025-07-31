#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Node
{
    char url[MAX_LEN];
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

Stack *initStack()
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->top = NULL;
    return st;
}

Queue *initQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void pushStack(Stack *st, char url[MAX_LEN])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->next = st->top;
    st->top = newNode;
}

int emptyStack(Stack *st)
{
    return st->top == NULL;
}

void popStack(Stack *st)
{
    if (emptyStack(st))
    {
        printf("Stack is empty!\n");
        return;
    }
    Node *tmp = st->top;
    st->top = tmp->next;
    free(tmp);
}

void pushQueue(Queue *q, char url[MAX_LEN])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int emptyQueue(Queue *q)
{
    return q->front == NULL;
}

void popQueue(Queue *q)
{
    if (emptyQueue(q))
    {
        printf("Queue is empty!\n");
        return;
    }
    Node *tmp = q->front;
    q->front = tmp->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(tmp);
}

Node *topStack(Stack *st)
{
    if (emptyStack(st))
    {
        printf("Stack is empty!\n");
        return NULL;
    }
    return st->top;
}

void displayQueue(Queue *q)
{
    if (emptyQueue(q))
    {
        printf("Queue is empty!\n");
        return;
    }
    Node *tmp = q->front;
    int i = 1;
    while (tmp != NULL)
    {
        printf("%d. %s\n", i, tmp->url);
        tmp = tmp->next;
        i++;
    }
}

void displayStack(Stack *st)
{
    if (emptyStack(st))
    {
        printf("Stack is empty!\n");
        return;
    }
    Node *tmp = st->top;
    int i = 1;
    while (tmp != NULL)
    {
        printf("%d. %s\n", i, tmp->url);
        tmp = tmp->next;
        i++;
    }
}
Node *frontQueue(Queue *q)
{
    if (emptyQueue(q))
    {
        printf("Queue is empty!\n");
        return NULL;
    }
    return q->front;
}

void freeStack(Stack *st)
{
    Node *tmp = st->top;
    while (tmp != NULL)
    {
        Node *temp = tmp;
        tmp = tmp->next;
        free(temp);
    }
}

void freeQueue(Queue *q)
{
    Node *tmp = q->front;
    while (tmp != NULL)
    {
        Node *temp = tmp;
        tmp = tmp->next;
        free(temp);
    }
}

void menu()
{
    printf("1. Mo tab moi\n");
    printf("2. Dong tab hien tai\n");
    printf("3. Chuyen den tab mo gan nhat\n");
    printf("4. Lich su dong tab\n");
    printf("5. Khoi phuc tab\n");
    printf("6. Hien thi tat ca tab\n");
    printf("0. Thoat chuong trinh\n");
}

int main()
{
    int choice;
    Stack *tabStack = initStack();
    Queue *closeQueue = initQueue();

    do
    {
        menu();
        printf("Nhap lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();
        if (choice == 1)
        {
            char tmp[MAX_LEN];
            printf("Nhap url: ");
            fgets(tmp, 100, stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            pushStack(tabStack, tmp);
        }
        else if (choice == 2)
        {
            Node *tmp = topStack(tabStack);
            pushQueue(closeQueue, tmp->url);
            popStack(tabStack);
        }
        else if (choice == 3)
        {
            Node *tmp = topStack(tabStack);
            if (tmp != NULL)
                printf("Ban dang o trang %s\n", tmp->url);
        }
        else if (choice == 4)
        {
            displayQueue(closeQueue);
        }
        else if (choice == 5)
        {
            Node *tmp = frontQueue(closeQueue);
            pushStack(tabStack, tmp->url);
            popQueue(closeQueue);
        }
        else if (choice == 6)
        {
            displayStack(tabStack);
        }
        else if (choice == 0)
        {
            printf("Da thoat chuong trinh");
            freeQueue(closeQueue);
            freeStack(tabStack);
            free(closeQueue);
            free(tabStack);
        }
    } while (choice != 0);
}
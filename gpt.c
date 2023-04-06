#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Linked list node
typedef int value_t;
typedef struct Node
{
    value_t data;
    struct Node *next;
} StackNode;

// Global mutex lock
pthread_mutex_t lock;

// Stack function declarations
void push(value_t v, StackNode **top);
value_t pop(StackNode **top);
int is_empty(StackNode *top);

int main(void)
{
    StackNode *top = NULL;

    push(5, &top);
    push(10, &top);
    pop(&top);
    push(15, &top);
    pop(&top);
    pop(&top);
    push(20, &top);

    push(-5, &top);
    pop(&top);
    push(-10, &top);
    pop(&top);
    pop(&top);
    push(-15, &top);
    pop(&top);
    push(-20, &top);

    return 0;
}

// Stack function definitions
void push(value_t v, StackNode **top)
{
    pthread_mutex_lock(&lock);

    StackNode *new_node = malloc(sizeof(StackNode));

    new_node->data = v;
    new_node->next = *top;
    *top = new_node;

    pthread_mutex_unlock(&lock);
}

value_t pop(StackNode **top)
{
    pthread_mutex_lock(&lock);

    if (is_empty(*top))
    {
        pthread_mutex_unlock(&lock);
        return (value_t)0;
    }

    value_t data = (*top)->data;
    StackNode *temp = *top;
    *top = (*top)->next;

    free(temp);

    pthread_mutex_unlock(&lock);

    return data;
}

int is_empty(StackNode *top)
{
    if (top == NULL) return 1;
    else return 0;
}


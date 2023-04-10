#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_THREADS 2
#define TEST_LOOPS 500

typedef int value_t;
typedef struct Node
{
    value_t data;
    struct Node *next;
} StackNode;
pthread_mutex_t lock;

void push(value_t v, StackNode **top);
value_t pop(StackNode **top);
int is_empty(StackNode *top);
void PrintStack(StackNode *top);
void testStack(StackNode **top);
void *ThreadFunction(void *arg);

int main(void)
{
    printf("starting\n");
    StackNode *top = NULL;

    pthread_t threads[NUM_OF_THREADS];

    for (int i = 0; i < NUM_OF_THREADS; i++) {
        int rc = pthread_create(&threads[i], NULL, ThreadFunction, (void*) top);
        if (rc) {
            printf("Error creating thread %d\n", i);
            return -1;
        }
    }

    for (int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void push(value_t v, StackNode **top)
{
    pthread_mutex_lock(&lock);

    StackNode * new_node = malloc(sizeof(StackNode));

    new_node->data = v;
    new_node->next = *top;
    *top           = new_node;

    pthread_mutex_unlock(&lock);
}

value_t pop(StackNode **top)
{
    pthread_mutex_lock(&lock);

    if (is_empty(*top)) return (value_t)0;
    value_t data  = (*top)->data; StackNode * temp  = *top;
    *top = (*top)->next;
    free(temp);

    pthread_mutex_unlock(&lock);

    return data;
}

int is_empty(StackNode *top) {
    if (top == NULL) return 1;
    else return 0;
}

void PrintStack(StackNode *top){
    printf("[ ");
    while (top != NULL){
        int data = top->data;
        printf("%d ",data);
        top = top->next;
    }
    printf("]\n");
}

void testStack(StackNode **top){
    printf("RUNNING TEST\t");
    for (int i = 0; i < TEST_LOOPS; i++){
        push(15, top);
        pop(top);
        push(42, top);
        pop(top);
        push(55, top);
        pop(top);
    }
}

void *ThreadFunction(void *arg){
    testStack(&arg);
    return NULL;
}

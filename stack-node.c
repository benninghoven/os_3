#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

typedef int value_t;
typedef struct Node {
    value_t data;
    struct Node *next;
} StackNode;
pthread_mutex_t lock;

void    push    (value_t v, StackNode **top);
value_t pop     (StackNode **top);
int     is_empty(StackNode *top);

void *t
read_func(void *arg);

void testStack(StackNode **top);

void PrintStack(StackNode *top);



int main(void)
{
    StackNode *top = NULL;

    pthread_t threads[NUM_THREADS];

  
    for (int i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_create(&threads[i], NULL, thread_func, (void*) top);
        if (rc) {
            printf("Error creating thread %d\n", i);
            return -1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
       push(5, *top);
       push(10,*top);
       pop (   *top);
    return 0;
}

void push(value_t v, StackNode **top) {
    pthread_mutex_lock(&lock);
    StackNode* new_node = malloc(sizeof(StackNode));
    new_node->data = v;
    new_node->next = *top;
    *top           = new_node;
    pthread_mutex_unlock(&lock);
}

value_t pop(StackNode **top) {
    pthread_mutex_lock(&lock);
    if (is_empty(*top)) return (value_t)0;
    value_t     data  = (*top)->data;
    StackNode * temp  = *top;
    *top              = (*top)->next;
    free(temp);
    pthread_mutex_unlock(&lock);
    return data;
}

int is_empty(StackNode *top) {
    if (top == NULL) return 1;
    else             return 0;
}

void *thread_func(void *arg) {
    StackNode **top = (StackNode**) arg;
    printf("Thread running\n");
    pthread_exit(NULL);
}

void testStack(StackNode **top) {
    for (int i = 0; i < 500; i++) {
       push(15,&top);
    }
}

void printStack(StackNode *top) {
}


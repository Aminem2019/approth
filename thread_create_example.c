#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gettid.h"

/* function definition respects pthread_create prototype */
static void *hello(void *arg)
{
    printf("Hello world from pid %d tid %d!\n", getpid(), gettid());
    return NULL;
}

void execute_in_thread(void *func(void*))
{
    pthread_t thread_id;
    /* create a thread */
    pthread_create(&thread_id, NULL, hello, NULL);
    /* wait for thread to finish */
    pthread_join(thread_id, NULL); 
}

int main()
{
    hello(NULL);
    execute_in_thread(hello);
    return 0;
}

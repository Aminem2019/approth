#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void __hello(char *name)
{
    printf("Hello from %-14s pid %d! parent pid %d\n", name, getpid(), getppid());
}

/* function definition respects pthread_create prototype */
static void *hello_thread(void *arg)
{
    __hello("thread-child");
    return NULL;
}

void execute_in_thread(void *func(void*))
{
    pthread_t thread_id;
    __hello("thread-parent");
    /* create a thread */
    pthread_create(&thread_id, NULL, func, NULL);
    /* wait for thread to finish */
    pthread_join(thread_id, NULL); 
}

void thread_example(void)
{
    execute_in_thread(hello_thread);
    while(1);
}

void fork_hello(void)
{
    __hello("fork-child");
    while(1);
}

void execute_in_process(void func(void));

void fork_example(void)
{
    __hello("fork-parent");
    execute_in_process(fork_hello);
    while(1);
}

void exec_example(void)
{
    // get PID
    int pid = getpid();
    char spid[10];
    sprintf(spid, "%d!", pid);
    // get PPID
    int ppid = getppid();
    char sppid[10];
    sprintf(sppid, "%d", ppid);
    // call exec  to load a new image
    execlp("echo", "echo", "Hello from exec           pid", spid, "parent pid", sppid, NULL);
    while(1);
}

void execute_in_process(void func(void))
{
    int pid = fork();
    /* 0 is returned to the child */
    if (pid == 0) {
        func();
        exit(0);
    }
}

int main()
{
    __hello("main-proc");
    execute_in_process(fork_example);
    execute_in_process(thread_example);
    execute_in_process(exec_example);
    while(1);
    return 0;
}

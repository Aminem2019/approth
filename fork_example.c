#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void hello(void)
{
    printf("Hello world from pid %d!\n", getpid());
}

void execute_in_process(void func(void))
{
    int pid = fork();
    /* 0 is returned to the child */
    if (pid == 0) {
        func();
        exit(0);
    }
    wait(NULL);
}

int main()
{
    hello();
    execute_in_process(hello);
    return 0;
}

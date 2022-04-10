#include <stdio.h>
#include <unistd.h>

int main()
{
    execlp("echo", "echo", "Hello world from echo!", NULL);
    return 0;
}



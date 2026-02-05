#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    //Creates child from parent
    if(fork() == 0)
    {
        //Creates grandchild from child
        if(fork() == 0)
        {
            //Grandchild
            printf("[Grandchild] ");
        }
        else
        {
            //Child
            wait(NULL);
            printf("[Child] ");
        }
    }
    else
    {
        //Parent
        wait(NULL);
        printf("[Parent] ");
    }

    //Warning: all converge here
    printf("PID: %d, PPID: %d\n", getpid(), getppid());
    exit(0);
}
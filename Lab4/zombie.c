#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    if(fork() == 0)
    {
        //Child
        exit(0);
    }
    else
    {
        //Parent
        sleep(10);
        printf("Zombie created. Run 'ps -l' now.\n");
    }
    exit(0);
}
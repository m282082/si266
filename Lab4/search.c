#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int A[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 };
    int length = sizeof(A) / sizeof(A[0]);

    int target = 15;
    //Creates Child from parent
    if(fork() == 0)
    {
        //Child
        for(int i = 0; i < length/2; i++)
        {
            if(A[i] == target)
            {
                exit(1);
            }
        }
        exit(0);
    }
    else
    {
        //Parent
        for(int i = length/2; i < length; i++)
        {
            if(A[i] == target)
            {
                //If parent found
                wait(NULL);
                printf("Found!\n");
                exit(0);
            }
        }

        //If parent did not find
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            if(WEXITSTATUS(status))
            {
                printf("Found!\n");
                exit(0);
            }
        }
        else
        {
            printf("Error: Child\n");
            exit(1);
        }
    }

    printf("Error: reached end of program\n");
    exit(1);
}
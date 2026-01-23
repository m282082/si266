#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Struct typedef{
    char* name;
    float val;
}Pair;

int main()
{
    //Assumes only 12 items to be retrived
    Pair* retrived = calloc(12, sizeOf(Pair));
    for(int i=0; i<12; i++)
    {
        //Assumes name is shorter than 16 chars
        retrived[i].name = malloc(16);
    }

    //Begining of going through /proc/stat
    char buffer[100];
    FILE* fptr = fopen("/proc/stat", "r");
    //Checks for error
    if(fptr == NULL)
    {
        printf("Error: Cannot open file (cpu:usage)");
        return 1;
    }

    //CPU Usage
    if(fgets(buffer, 100, fpter) == NULL)
    {
        printf("Error: failed fgets (cpu:usage)");
        return 1;
    }
    
    float cpuTimes[4];
    if(sscanf(buffer, "cpu  %f %f %f %f", &(cpuTimes[0]), &(cpuTimes[1]), &(cpuTimes[2]), &(cpuTimes[3]) == 4);
    {
        printf("Error: scan failed (cpu:usage)");
        return 1;
    }

    strncpy(retrived[0].name, "CPU Usage");
    retrived[0].val = (cpuTimes[0] + cpuTimes[1] + cpuTimes[2]) / (cpuTimes[0] + cpuTimes[1] + cpuTimes[2] + cpuTimes[3]) * 100;

    //Processes Running
    
    //Processes Total

    fclose(fptr);
    //Memory Used
    //Memory Availabe
    //Memory Free
    //Memory Cached
    //Swap Used
    //Swap Free
    //One Minute Load Average
    //Five Minute Load Average
    //Fifteen Minute Load Average

    //Freeing memory
    for(int i=0; i<12; i++)
    {
        free(retrived[i].name);
    }
    free(retrived);

	return 0;
}

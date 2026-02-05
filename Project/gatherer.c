#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* name;
    float fval;
    int ival;
}Pair;

int main()
{
    //Assumes only 12 items to be retrived
    Pair* retrived = calloc(12, sizeof(Pair));
    for(int i=0; i<12; i++)
    {
        //Assumes name is shorter than 16 chars
        retrived[i].name = malloc(16);
    }

    //Begining of going through /proc/stat
    char buffer[100];
    FILE* statPtr = fopen("/proc/stat", "r");
    //Checks for error
    if(statPtr == NULL)
    {
        printf("Error: Cannot open file (cpu:usage)");
        return 1;
    }



    //CPU Usage
    if(fgets(buffer, 100, statPtr) == NULL)
    {
        printf("Error: failed fgets (cpu:usage)");
        return 1;
    }
    
    float cpuTimes[4];
    if(sscanf(buffer, "cpu  %f %f %f %f", &(cpuTimes[0]), &(cpuTimes[1]), &(cpuTimes[2]), &(cpuTimes[3])) != 4)
    {
        printf("Error: scan failed (cpu:usage)");
        return 1;
    }

    strncpy(retrived[0].name, "CPU_USAGE", 15);
    retrived[0].fval = (cpuTimes[0] + cpuTimes[1] + cpuTimes[2]) / (cpuTimes[0] + cpuTimes[1] + cpuTimes[2] + cpuTimes[3]) * 100;

    //Memory Used
    strncpy(retrived[1].name, "MEM_USED", 15);
    retrived[1].fval = 0;

    //Memory Availabe
    strncpy(retrived[2].name, "MEM_AVAIL", 15);
    retrived[2].fval = 0;

    //Memory Free
    strncpy(retrived[3].name, "MEM_FREE", 15);
    retrived[3].fval = 0;

    //Memory Cached
    strncpy(retrived[4].name, "MEM_CACHED", 15);
    retrived[4].fval = 0;

    //Swap Used
    strncpy(retrived[5].name, "SWAP_USED", 15);
    retrived[5].fval = 0;

    //Swap Free
    strncpy(retrived[6].name, "SWAP_FREE", 15);
    retrived[6].fval = 0;

    //One Minute Load Average
    strncpy(retrived[7].name, "LOAD_1", 15);
    retrived[7].fval = 0;

    //Five Minute Load Average
    strncpy(retrived[8].name, "LOAD_5", 15);
    retrived[8].fval = 0;

    //Fifteen Minute Load Average
    strncpy(retrived[9].name, "LOAD_15", 15);
    retrived[9].fval = 0;

    //Processes Running
    strncpy(retrived[10].name, "PROC_RUN", 15);
    retrived[10].ival = 0;
    
    //Processes Total
    strncpy(retrived[11].name, "PROC_TOTAL", 15);
    retrived[11].ival = 0;

    //Printing
    for(int i=0; i<10; i++)
    {
        printf("%s:%.2f,", retrived[i].name, retrived[i].fval);
    }
    printf("%s:%d,%s:%d\n", retrived[10].name, retrived[10].ival, retrived[11].name, retrived[11].ival);

    //Freeing memory
    for(int i=0; i<12; i++)
    {
        free(retrived[i].name);
    }
    free(retrived);

    //Close files
    fclose(statPtr);

	return 0;
}

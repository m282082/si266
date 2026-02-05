#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    char* name;
    float fval;
    int ival;
}Pair;

void ProcessStat(Pair* A);
void ProcessMeminfo(Pair* A);
void ProcessLoadavg(Pair* A);

int main()
{
    //Assumes only 12 items to be retrived
    Pair* retrived = calloc(12, sizeof(Pair));
    for(int i=0; i<12; i++)
    {
        //Assumes name is shorter than 16 chars
        retrived[i].name = malloc(16);
    }

    ProcessStat(retrived);

    ProcessMeminfo(retrived);

    ProcessLoadavg(retrived);

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

	return 0;
}

int ProcessValuePair(FILE* fPtr, char* name)
{
    char buffer[100];
    if(fgets(buffer, 100, fPtr) == NULL)
    {
        printf("Error: failed fgets (%s)", name);
        exit(1);
    }

    int val;
    if(sscanf(buffer, "%*s%d", &val) != 1)
    {
        printf("Error: scan failed (%s)", name);
        exit(1);
    }

    return val;
}

void ProcessStat(Pair* A)
{
    char buffer[100];
    FILE* fPtr = fopen("/proc/stat", "r");
    //Checks for error
    if(fPtr == NULL)
    {
        printf("Error: Cannot open file (/proc/stat)");
        exit(1);
    }

    //First check of CPU Usage
    if(fgets(buffer, 100, fPtr) == NULL)
    {
        printf("Error: failed fgets (CPU_USAGE_1)");
        exit(1);
    }
    
    int bufferMove;
    float cpuTimesFirst[8];
    if(sscanf(buffer, "%*s%n", &bufferMove) < 0)
    {
        printf("Error: scan failed (CPU_USAGE_1)");
        exit(1);
    }

    for(int i = 0; i < 8; i++)
    {
        int n;
        if(sscanf(buffer + bufferMove, "%f %n", &(cpuTimesFirst[i]), &n) != 1)
        {
            printf("%d", i);
	    printf("Error: scan failed (CPU_USAGE_1)");
            exit(1);
        }
        bufferMove += n;
    }

    fclose(fPtr);
    sleep(1);

    fPtr = fopen("/proc/stat", "r");
    //Checks for error
    if(fPtr == NULL)
    {
        printf("Error: Cannot open file (/proc/stat)");
        exit(1);
    }

    //Second check of CPU Usage
    if(fgets(buffer, 100, fPtr) == NULL)
    {
        printf("Error: failed fgets (CPU_USAGE_2)");
        exit(1);
    }
    
    bufferMove = 0;
    float cpuTimesSecond[8];
    if(sscanf(buffer, "%*s%n", &bufferMove) < 0)
    {
        printf("Error: scan failed (CPU_USAGE_2)");
        exit(1);
    }

    for(int i = 0; i < 8; i++)
    {
        int n;
        if(sscanf(buffer + bufferMove, "%f %n", &(cpuTimesSecond[i]), &n) != 1)
        {
            printf("Error: scan failed (CPU_USAGE_2)");
            exit(1);
        }
        bufferMove += n;
    }
    int D_tot = 0;
    int D_work = 0;
    for(int i = 0; i < 8; i++)
    {
        D_tot += cpuTimesFirst[i] + cpuTimesSecond[i]; 
        if(i != 3 && i != 4){ D_work += cpuTimesFirst[i] + cpuTimesSecond[i];}   
    }

    //CPU Usage
    strncpy(A[0].name, "CPU_USAGE", 15);
    A[0].fval = ((float)D_work / D_tot) * 100;

    //Gets buffer to the bottom of the file
    char find[16] = "";
    while(strcmp(find, "processes") != 0)
    {
        if(fgets(buffer, 100, fPtr) == NULL)
        {
            printf("Error: failed fgets (PROC_TOTAL)");
            exit(1);
        }

        if(sscanf(buffer, "%s", find) != 1)
        {
            printf("Error: scan failed (PROC_TOTAL)");
            exit(1);
        }
    }

    //Processes Total
    strncpy(A[11].name, "PROC_TOTAL", 15);
    if(sscanf(buffer, "%*s%d", &(A[11].ival)) != 1)
    {
        printf("Error: scan failed (PROC_TOTAL)");
        exit(1);
    }
    
    if(fgets(buffer, 100, fPtr) == NULL)
    {
        printf("Error: failed fgets (PROC_TOTAL)");
        exit(1);
    }

    //Processes Running
    strncpy(A[10].name, "PROC_RUN", 15);
    if(sscanf(buffer, "%*s%d", &(A[10].ival)) != 1)
    {
        printf("Error: scan failed (PROC_TOTAL)");
        exit(1);
    }

    fclose(fPtr);
}

void ProcessMeminfo(Pair* A)
{
    FILE* fPtr = fopen("/proc/meminfo", "r");
    //Checks for error
    if(fPtr == NULL)
    {
        printf("Error: Cannot open file (/proc/meminfo)");
        exit(1);
    }

    //Gets total memory
    int totMem = ProcessValuePair(fPtr, "Total_Mem");

    //Memory Free
    int totMemFree = ProcessValuePair(fPtr, "MEM_FREE");
    strncpy(A[3].name, "MEM_FREE", 15);
    A[3].fval = (float)totMemFree / totMem;

    //Memory Availabe
    int totMemAvail = ProcessValuePair(fPtr, "MEM_FREE");
    strncpy(A[2].name, "MEM_AVAIL", 15);
    A[2].fval = (float)totMemAvail / totMem;

    //Memory Used
    strncpy(A[1].name, "MEM_USED", 15);
    A[1].fval = (float)(totMem - totMemAvail) / totMem;


    //Memory Cached
    //Skips a line
    ProcessValuePair(fPtr, "MEM_CACHED");
    int totMemCach = ProcessValuePair(fPtr, "MEM_CACHED");
    strncpy(A[4].name, "MEM_CACHED", 15);
    A[4].fval = (float)totMemCach / totMem;

    //Gets total Swap
    //Skips 9 lines and gets Swap
    int totSwap;
    for(int i = 0; i < 10; i++)
    {
        totSwap = ProcessValuePair(fPtr, "Total_Swap");
    }

    //Swap Free
    int totSwapFree = ProcessValuePair(fPtr, "SWAP_FREE");
    strncpy(A[6].name, "SWAP_FREE", 15);
    A[6].fval = (float)totSwapFree / totSwap;

    //Swap Used
    strncpy(A[5].name, "SWAP_USED", 15);
    A[5].fval = (float)(totSwap - totSwapFree) / totSwap;

    fclose(fPtr);
}

void ProcessLoadavg(Pair* A)
{
    char buffer[100];
    FILE* fPtr = fopen("/proc/loadavg", "r");
    //Checks for error
    if(fPtr == NULL)
    {
        printf("Error: Cannot open file (/proc/loadavg)");
        exit(1);
    }

    if(fgets(buffer, 100, fPtr) == NULL)
    {
        printf("Error: failed fgets (/proc/loadavg)");
        exit(1);
    }

    //One Minute Load Average
    strncpy(A[7].name, "LOAD_1", 15);
    //Five Minute Load Average
    strncpy(A[8].name, "LOAD_5", 15);
    //Fifteen Minute Load Average
    strncpy(A[9].name, "LOAD_15", 15);

    if(sscanf(buffer, "%f %f %f", &(A[7].fval), &(A[8].fval), &(A[9].fval)) != 3)
    {
        printf("Error: scan failed (/proc/loadavg)");
        exit(1);
    }
}

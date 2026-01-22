#include <stdio.h>
#include<stdlib.h>
#include <string.h>

int main()
{
    //Gets file pointer
    FILE* fptr = fopen("sensors.dat", "r");
    //Checks if open
    if(fptr == NULL)
    {
        printf("Error: Not able to open file");
        return 1;
    }

    //Assumes lines are less than 100 chars long
    char buffer[100];
    while(1)
    {
        //Checks for error
        if(fgets(buffer, sizeof(buffer), fptr) == NULL)
        {
            printf("Error: buffer retrive error");
            return 1;
        }

        //Handles parsing logic
        if(strcmp(buffer, "-- END DATA --\n") == 0)
        {
            break;
        }
        else if(buffer[0] == '#')
        {
            continue;
        }
        else
        {
            //Checks begining of line
            char check[4];
            int id;
            float temp[3];
            //Checks for error and scans buffer
            if(sscanf(buffer, "%3s %d | %f %f %f", check, &id, &(temp[0]), &(temp[1]), &(temp[2])) != 5 || strcmp(check, "ID:") != 0)
            {
                continue;
            }
            else
            {
                //Clean output
                float avgtemp = (temp[0] + temp[1] + temp[2]) / 3.0;
                printf("Sensor %d: Avg Temp = %.2f\n", id, avgtemp);
            }
        }
    }

    fclose(fptr);
    return 0;
} 

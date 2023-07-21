// myPackageObj.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/myPackageObj.h"

void createFileWithTime()
{
    // Check if the file already exists
    if (remove("/tmp/myPackageFile.txt") != 0)
    {
        printf("File does not exist or cannot be removed.\n");
    }

    // Get the current time
    time_t currentTime;
    time(&currentTime);
    struct tm* timeinfo = localtime(&currentTime);

    // Format the time as a string
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Create and write to the file
    FILE* file = fopen("/tmp/myPackageFile.txt", "w");
    if (file == NULL)
    {
        printf("Failed to create the file.\n");
        return;
    }

    fprintf(file, "File created at: %s\n", timeString);
    fclose(file);
}

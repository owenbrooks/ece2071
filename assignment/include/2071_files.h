// Functions for listing all files in a directory
#pragma once
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int store_filenames(const char *directory, char ***filenames)
{
    // Count number of files
    int file_count = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG) // ignores folders
            {
                file_count++;
            }
        }
        closedir(d);
    }

    // Allocate memory for filename pointers
    *filenames = (char **)malloc(file_count * sizeof(char *));

    // Store filenames
    int file_index = 0;
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                // printf("%s\n", dir->d_name);
                // Allocate memory for each string and copy it over
                int path_length = strlen(directory) + strlen(dir->d_name);
                (*filenames)[file_index] = (char *)malloc(path_length + 1);                           // TODO: double check +1
                snprintf((*filenames)[file_index], path_length + 2, "%s/%s", directory, dir->d_name); // TODO: confirm +2
                file_index++;
            }
        }
        closedir(d);
    }

    return file_count;
}

void print_files(const char *directory)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
}

#pragma once
#include <stdbool.h>
#include <string.h>

// Sort an array of pointers based on the "keys" in another array in ascending order
// based on https://www.geeksforgeeks.org/python-program-for-bubble-sort/
// TODO: a faster sorting algorithm
void sort_by_key(void *values[], float keys[], int n)
{
    // Create a copy of the keys so the original isn't modified
    int keys_copy[n];
    memcpy(keys_copy, keys, sizeof(keys_copy));

    // optimize code, so if the array is already sorted, it doesn't need
    // to go through the entire process
    bool swapped = false;
    // Traverse through all array elements
    for (int i = 0; i < n - 1; i++)
    {
        // range(n) also work but outer loop will
        // repeat one time more than needed.
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++)
        {
            // traverse the array from 0 to n-i-1
            // Swap if the element found is greater
            // than the next element
            if (keys_copy[j] > keys_copy[j + 1])
            {
                swapped = true;
                float temp_key = keys_copy[j];
                keys_copy[j] = keys_copy[j + 1];
                keys_copy[j + 1] = temp_key;

                void *temp_ptr = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp_ptr;
            }
        }

        if (!swapped)
        {
            // if we haven't needed to make a single swap, we
            // can just exit the main loop.
            return;
        }
    }
}

void sort_simple(float arr[], int n)
{
    // optimize code, so if the array is already sorted, it doesn't need
    // to go through the entire process
    bool swapped = false;
    // Traverse through all array elements
    for (int i = 0; i < n - 1; i++)
    {
        // range(n) also work but outer loop will
        // repeat one time more than needed.
        // Last i elements are already in place
        for (int j = 0; j < n - i - 1; j++)
        {
            // traverse the array from 0 to n-i-1
            // Swap if the element found is greater
            // than the next element
            if (arr[j] > arr[j + 1])
            {
                swapped = true;
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        if (!swapped)
        {
            // if we haven't needed to make a single swap, we
            // can just exit the main loop.
            return;
        }
    }
}
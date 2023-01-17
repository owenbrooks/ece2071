#include "2071_sort.h"
#include <stdio.h>

int main(void)
{
    float values[] = {1.0, 5.0, 4.0, 3.0, 6.0, 2.0};
    sort_simple(values, 6);
    for (int i = 0; i < 6; i++)
    {
        printf("%.1f ", values[i]);
    }
    printf("\n");

    float means[] = {1.0, 5.0, 4.0, 3.0, 6.0, 2.0};
    char *known_image_hashes[] = {"one", "five", "four", "three", "six", "two"};
    sort_by_key(known_image_hashes, means, 6);

    for (int i = 0; i < 6; i++)
    {
        printf("%s ", known_image_hashes[i]);
    }
    printf("\n");
}
#pragma once

typedef struct Image
{
    int height;
    int width;
    int *data_red;   // pointer to an array of length height * width
    int *data_green; // pointer to an array of length height * width
    int *data_blue;  // pointer to an array of length height * width
} Image;

// Example usage:
// Image *my_image;
// int red = my_image->data_red[71 * my_image->width + 20];

Image read_image_from_file(const char *filename) {
    Image image;
    return image;
}
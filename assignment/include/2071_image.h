// Functions for reading and writing images
#pragma once
#define STBI_ONLY_JPG // disables other image formats
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct Image
{
    int height;
    int width;
    int *data; // pointer to an array of length image.height * image.width
} Image;

// Example usage:
// Image my_image = read_image_from_file("test_image.png");
// int pixel_value = my_image.data[71 * my_image.width + 20];

Image read_image_from_file(const char *filename)
{
    Image image;
    int bytes_per_pixel;
    unsigned char *data = stbi_load(filename, &image.width, &image.height, &bytes_per_pixel, 0);

    // Check if file was loaded correctly
    if (data == NULL)
    {
        printf("Error: File not found or unable to be read: %s\n", filename);
        printf("%s\n", stbi__g_failure_reason);
        abort();
    }

    // Check that we are dealing with 8-bit greyscale only
    if (bytes_per_pixel != 1)
    {
        printf("Error: Program designed to only work with 8-bit greyscale images\n");
        abort();
    }

    // printf("File: '%s', width: %d, height: %d, %d byte(s) per pixel\n", filename, image.width, image.height, bytes_per_pixel);

    // Allocate space for image data
    image.data = malloc(image.width * image.height * sizeof(int));
    // Copy data into image struct
    for (int i = 0; i < image.width * image.height; i++)
    {
        image.data[i] = data[i];
    }

    stbi_image_free(data);
    return image;
}

void write_image_to_file(const char *filename, Image *image)
{
    // Allocate space for image data
    unsigned char *data = malloc(image->width * image->height * sizeof(unsigned char));

    // Copy data into image struct
    for (int i = 0; i < image->width * image->height; i++)
    {
        data[i] = image->data[i];
    }

    int channel_count = 1;
    int stride = channel_count * image->width;
    int write_result = stbi_write_png(filename, image->width, image->height, channel_count, data, stride);
}
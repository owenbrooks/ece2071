// Functions for transforming images
#pragma once
#include "2071_image.h"

// TODO: invert colours (not)
// TODO: chop it up?

void rot_90_anticlockwise(Image *image)
{
    // Create a temporary image to store the original pixels
    Image temp_image;
    temp_image.width = image->width;
    temp_image.height = image->height;
    temp_image.data = malloc(sizeof(int) * temp_image.width * temp_image.height);
    memcpy(temp_image.data, image->data, sizeof(int) * temp_image.width * temp_image.height); // copy the pixels

    // Slower copy implementation
    // for (int col = 0; col < image->width; col++)
    // {
    //     for (int row = 0; row < image->height; row++)
    //     {
    //         temp_image.data[row*image->width + col] = image->data[row * image->width + col];
    //     }
    // }

    for (int col = 0; col < image->width; col++)
    {
        for (int row = 0; row < image->height; row++)
        {
            int source_row = col;
            int source_col = image->width - row - 1;
            image->data[row * image->width + col] = temp_image.data[source_row * image->width + source_col];
        }
    }
}

void rot_90_clockwise(Image *image)
{
    // Create a temporary image to store the original pixels
    Image temp_image;
    temp_image.width = image->width;
    temp_image.height = image->height;
    temp_image.data = malloc(sizeof(int) * temp_image.width * temp_image.height);
    memcpy(temp_image.data, image->data, sizeof(int) * temp_image.width * temp_image.height); // copy the pixels

    // Slower copy implementation
    // for (int col = 0; col < image->width; col++)
    // {
    //     for (int row = 0; row < image->height; row++)
    //     {
    //         temp_image.data[row*image->width + col] = image->data[row * image->width + col];
    //     }
    // }

    for (int col = 0; col < image->width; col++)
    {
        for (int row = 0; row < image->height; row++)
        {
            int destination_row = col;
            int destination_col = image->width - row - 1;
            image->data[destination_row * image->width + destination_col] = temp_image.data[row * image->width + col];
        }
    }
}

// Flips image upside-down
void flip(Image *image)
{
    for (int col = 0; col < image->width; col++)
    {
        for (int row = 0; row < image->height / 2; row++)
        {
            int temp_pixel_copy = image->data[row * image->width + col];
            image->data[row * image->width + col] = image->data[(image->height - row - 1) * image->width + col];
            image->data[(image->height - row - 1) * image->width + col] = temp_pixel_copy;
        }
    }
}

// Flips image left-to-right
void mirror(Image *image)
{
    for (int col = 0; col < image->width / 2; col++)
    {
        for (int row = 0; row < image->height; row++)
        {
            int temp_pixel_copy = image->data[row * image->width + col];
            image->data[row * image->width + col] = image->data[row * image->width + (image->width - col - 1)];
            image->data[row * image->width + (image->width - col - 1)] = temp_pixel_copy;
        }
    }
}

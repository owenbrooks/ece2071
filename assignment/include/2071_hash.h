// Functions for calculating hashes
#pragma once
#include <tomcrypt.h>
#include "2071_image.h"

// Example usage:
// unsigned long inputSize = 5;
// const char * input = "input string";
// unsigned char* hashResult = hashSHA256(input, inputSize);
// printf("%s", hashResult);

/**
 * Hashes a given sequence of bytes using the SHA256 algorithm
 * @param input The input sequence pointer
 * @param inputSize The size of the input sequence
 * @return A malloc-allocated pointer to the resulting data. 20 bytes long.
 */
unsigned char *hashSHA256(const char *input, unsigned long inputSize)
{
    // Initial
    unsigned char *hashResult = (unsigned char *)malloc(sha256_desc.hashsize);
    // Initialize a state variable for the hash
    hash_state md;
    sha256_init(&md);
    // Process the text - remember you can call process() multiple times
    sha256_process(&md, (const unsigned char *)input, inputSize);
    // Finish the hash calculation
    sha256_done(&md, hashResult);
    // Return the result
    return hashResult;
}

// Hashes the data in a given image using the SHA256 algorithm
// returns a pointer to an array with the hash, of length sha256_desc.hashsize
unsigned char *hashSHA256Image(Image *image)
{
    int image_data_length = image->height * image->width;
    unsigned char *input_data = malloc(image_data_length * sizeof(unsigned char));

    // Copy to input_data buffer so it is the correct type for hashing
    for (int i = 0; i < image_data_length; i++)
    {
        input_data[i] = image->data[i];
    }

    // Initial
    unsigned char *hashResult = (unsigned char *)malloc(sha256_desc.hashsize);
    // Initialize a state variable for the hash
    hash_state md;
    sha256_init(&md);
    // Process the text - remember you can call process() multiple times
    sha256_process(&md, (const unsigned char *)input_data, image_data_length); // TODO: fix calculation
    // Finish the hash calculation
    sha256_done(&md, hashResult);

    free(input_data);

    // Return the result
    return hashResult;
}

void print_hash(unsigned char *hash)
{
    for (int x = 0; x < sha256_desc.hashsize; x++)
    {
        printf("%02x", hash[x]);
    }
    printf("\n");
}
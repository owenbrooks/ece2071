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
uint8_t *hashSHA256Image(Image *image)
{
    int image_data_length = image->height * image->width;
    uint8_t *input_data = malloc(image_data_length * sizeof(uint8_t));

    // Copy to input_data buffer so it is the correct type for hashing
    for (int i = 0; i < image_data_length; i++)
    {
        input_data[i] = image->data[i];
    }

    // Initial
    uint8_t *hashResult = malloc(sha256_desc.hashsize);
    // Initialize a state variable for the hash
    hash_state md;
    sha256_init(&md);
    // Process the text - remember you can call process() multiple times
    sha256_process(&md, (const uint8_t *)input_data, image_data_length); // TODO: fix calculation
    // Finish the hash calculation
    sha256_done(&md, hashResult);

    free(input_data);

    // Return the result
    return hashResult;
}

void print_hash(uint8_t *hash)
{
    for (int x = 0; x < sha256_desc.hashsize; x++)
    {
        printf("%02x", hash[x]);
    }
}

// Takes a string containing hex numbers and converts this to an array of uint8_t
// TODO: just store the hashes as char arrays everywhere to make this easier
void hash_string_to_array(uint8_t **dest, char *source)
{
    uint8_t *hash = malloc(sizeof(uint8_t) * sha256_desc.hashsize);

    const int number_of_chars_in_hash = sha256_desc.hashsize * 2;

    for (int x = 0; x < number_of_chars_in_hash/2; x++)
    {
        char hex_couplet[3];
        char *endptr = malloc(256);
        snprintf(hex_couplet, 3, "%c%c", source[2*x], source[2*x+1]);
        uint8_t extracted = strtol(hex_couplet, endptr, 16);
        hash[x] = extracted; 
    }
    *dest = hash;
}

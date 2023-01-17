#include <stdio.h>
#include "2071_image.h"
#include "2071_hash.h"
#include "2071_stats.h"
#include "2071_files.h"
#include <stdbool.h>

int find_match(unsigned char *unknown_hash, unsigned char **known_hashes, int known_hashes_length)
{
    int hashsize = sha256_desc.hashsize;

    // Loop through all known hashes
    int matching_index = -1;
    for (int hash_index = 0; hash_index < known_hashes_length; hash_index++)
    {
        // Compare to the unknown hash, stop looping if equal
        unsigned char *known_hash = known_hashes[hash_index];
        // print_hash(known_hash);
        // print_hash(unknown_hash);
        bool found_match = true;
        for (int byte_index = 0; byte_index < hashsize; byte_index++)
        {
            if (unknown_hash[byte_index] != known_hash[byte_index])
            {
                found_match = false;
                break;
            }
        }
        if (found_match)
        {
            matching_index = hash_index;
            break;
        }

    }
    return matching_index;
}

int main(int argc, char *argv[])
{
    char **known_image_names; // pointer to an array of filenames
    char **unknown_image_names;
    char *known_image_dir = argv[0];
    char *unknown_image_dir = argv[1];
    int known_images_length = store_filenames(known_image_dir, &known_image_names);
    int unknown_images_length = store_filenames(unknown_image_dir, &unknown_image_names);

    double known_image_means_red[known_images_length];
    unsigned char *known_image_hashes[known_images_length];

    printf("Beginning Stage 1: Image Statistics and Hashing...\n");

    // Compute hashes of all known images
    for (int known_index = 0; known_index < known_images_length; known_index++)
    {
        const char *known_image_filename = known_image_names[known_index];
        Image known_image = read_image_from_file(known_image_filename);

        double mean = compute_mean(known_image.data, known_image.width * known_image.height);
        double variance = compute_variance(known_image.data, known_image.width * known_image.height);

        known_image_hashes[known_index] = hashSHA256Image(&known_image);

        // Print the hash
        // print_hash(known_image_hashes[known_index]);
        // // Print the stats
        // printf(", mean: %f, var: %f", mean, variance);
        // printf(", width: %d, height: %d", known_image.width, known_image.height);
        // printf("\n");

        free(known_image.data);
    }

    printf("Beginning Stage 2: Search...\n");

    // Compute hashes of all unknown images, and find the hash matches for the known images
    for (int unknown_index = 0; unknown_index < unknown_images_length; unknown_index++)
    {
        const char *unknown_image_filename = unknown_image_names[unknown_index];
        Image unknown_image = read_image_from_file(unknown_image_filename);

        unsigned char *unknown_hash = hashSHA256Image(&unknown_image);

        // Find and report match
        int match_index = find_match(unknown_hash, known_image_hashes, known_images_length);
        if (match_index != -1)
        {
            printf("Found match! Image %s matches patient ID %s.\n", unknown_image_names[unknown_index], known_image_names[match_index]);
        }
        else
        {
            printf("No match found for image %s.\n", unknown_image_names[unknown_index]);
        }

        free(unknown_image.data);
    }
}

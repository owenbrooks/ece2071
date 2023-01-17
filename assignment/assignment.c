#include <stdio.h>
#include "2071_image.h"
#include "2071_hash.h"
#include "2071_stats.h"
#include "2071_files.h"

int find_match(unsigned char *mystery_hash, unsigned char **known_hashes, int known_hashes_length)
{
    return -1; // TODO: implement
}

int main(void)
{
    char **known_image_names; // pointer to an array of filenames
    int file_count = store_filenames("dataset_a/known", &known_image_names);

    const char *mystery_image_names[] = {"unknown1.png", "unknown2.png", "unknown3.png"};
    int known_images_length = 100;
    int mystery_images_length = 10;

    double known_image_means_red[known_images_length];
    unsigned char *known_image_hashes[known_images_length];

    printf("Beginning Stage 1: Image Statistics and Hashing...\n");

    // Compute hashes of all known images
    for (int known_index = 0; known_index < known_images_length; known_index++)
    {
        const char *known_image_filename = known_image_names[known_index];
        Image known_image = read_image_from_file(known_image_filename);

        // for (int i = 0; i < known_image.width; i++) {
        //     for (int j = 0; j < known_image.height; j++) {
        //         printf("%d ", known_image.data[j*known_image.width + i]);
        //     }
        //     printf("\n");
        // }
        double mean = compute_mean(known_image.data, known_image.width * known_image.height);
        double variance = compute_variance(known_image.data, known_image.width * known_image.height);

        known_image_hashes[known_index] = hashSHA256Image(&known_image);

        // Print the hash
        printf("hash: ");
        for (int x = 0; x < sha256_desc.hashsize; x++)
        {
            printf("%02x", known_image_hashes[known_index][x]);
        }
        // Print the stats
        printf(", mean: %f, var: %f", mean, variance);
        printf(", width: %d, height: %d", known_image.width, known_image.height);
        printf("\n");

        free(known_image.data);
    }

    printf("Beginning Stage 2: Search...\n");

    // Compute hashes of all mystery images, and find the hash matches for the known images
    for (int mystery_index = 0; mystery_index < mystery_images_length; mystery_index++)
    {
        const char *mystery_image_filename = known_image_names[mystery_index];
        Image mystery_image = read_image_from_file(mystery_image_filename);

        unsigned char *mystery_hash = hashSHA256Image(&mystery_image);

        // Find and report match
        int match_index = find_match(mystery_hash, known_image_hashes, known_images_length);
        if (match_index != -1)
        {
            printf("Found match! Image %s matches patient ID %s.\n", mystery_image_names[mystery_index], known_image_names[match_index]);
        }

        free(mystery_image.data);
    }
}

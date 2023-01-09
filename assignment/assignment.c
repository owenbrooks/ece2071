#include <stdio.h>
#include "Image.h"
#include "hash.h"
#include "stats.h"

int find_match(unsigned char *mystery_hash, unsigned char **known_hashes, int known_hashes_length)
{
    return 0; // TODO: implement
}

int main(void)
{
    const char *known_image_names[] = {"ID1234.png", "ID1235.png", "ID1236.png", "ID1237.png"};
    const char *mystery_image_names[] = {"unknown1.png", "unknown2.png", "unknown3.png"};
    int known_images_length = 1000;
    int mystery_images_length = 10;

    double known_image_means_red[known_images_length];
    unsigned char *known_image_hashes[known_images_length];

    printf("Beginning Stage 1: Image Statistics and Hashing...\n");

    // Compute hashes of all known images
    for (int known_index = 0; known_index < known_images_length; known_index++)
    {
        const char *known_image_filename = known_image_names[known_index];
        Image known_image = read_image_from_file(known_image_filename);

        known_image_hashes[known_index] = hashSHA256Image(&known_image);
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
    }
}

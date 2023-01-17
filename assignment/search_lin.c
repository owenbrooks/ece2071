#include <stdio.h>
#include "2071_image.h"
#include "2071_hash.h"
#include "2071_stats.h"
#include "2071_files.h"
#include <stdbool.h>

int find_match(uint8_t *unknown_hash, uint8_t **known_hashes, int known_hashes_length)
{
    int hashsize = sha256_desc.hashsize;

    // Loop through all known hashes
    int matching_index = -1;
    for (int hash_index = 0; hash_index < known_hashes_length; hash_index++)
    {
        // Compare to the unknown hash, stop looping if equal
        uint8_t *known_hash = known_hashes[hash_index];
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

// Usage: search dataset_a/known dataset_a/unknown_no_transform hashes.txt
int main(int argc, char *argv[])
{
    char **known_image_names; // pointer to an array of filenames
    char **unknown_image_names;
    char *known_image_dir = argv[1];
    char *unknown_image_dir = argv[2];
    int known_images_length = store_filenames(known_image_dir, &known_image_names);
    int unknown_images_length = store_filenames(unknown_image_dir, &unknown_image_names);

    uint8_t *known_image_hashes[known_images_length];

    // Read in hashes of all known images
    char *hashes_filename = argv[3];
    FILE *hash_file = fopen (hashes_filename, "r");
    char raw_hash_string[100];

    int hash_index = 0;
    while (fscanf(hash_file, "%s", raw_hash_string) == 1)
    {
        hash_string_to_array(&known_image_hashes[hash_index], raw_hash_string); // TODO: remove the need for this
        // printf("%s\n", raw_hash_string);
        // print_hash(known_image_hashes[hash_index]);
        // printf("\n");
        hash_index++;
    }

    // Compute hashes of all unknown images, and find the hash matches for the known images
    printf("unknown known\n");
    for (int unknown_index = 0; unknown_index < unknown_images_length; unknown_index++)
    {
        const char *unknown_image_filename = unknown_image_names[unknown_index];
        Image unknown_image = read_image_from_file(unknown_image_filename);

        unsigned char *unknown_hash = hashSHA256Image(&unknown_image);

        // Find and report match
        int match_index = find_match(unknown_hash, known_image_hashes, known_images_length);

        if (match_index != -1)
        {
            // printf("Found match! Image %s matches patient ID %s.\n", unknown_image_names[unknown_index], known_image_names[match_index]);
            printf("%s %s\n", unknown_image_names[unknown_index], known_image_names[match_index]);
        }
        else
        {
            printf("No match found for image %s.\n", unknown_image_names[unknown_index]);
        }

        free(unknown_image.data);
    }
}

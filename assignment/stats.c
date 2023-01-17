#include <stdio.h>
#include "2071_image.h"
#include "2071_hash.h"
#include "2071_stats.h"
#include "2071_files.h"

int main(int argc, char *argv[])
{
    char **known_image_names; // pointer to an array of filenames
    char *known_image_dir = argv[1];
    int known_images_length = store_filenames(known_image_dir, &known_image_names);

    uint8_t *known_image_hashes[known_images_length];

    // FILE *hashes_file = fopen("hashes.txt", "w"); // write only 
           
    // if (hashes_file == NULL) 
    // {   
    //     printf("Error! Could not open file\n"); 
    //     return -1;
    // } 

    // Compute hashes of all known images
    for (int known_index = 0; known_index < known_images_length; known_index++)
    {
        const char *known_image_filename = known_image_names[known_index];
        Image known_image = read_image_from_file(known_image_filename);

        double mean = compute_mean(known_image.data, known_image.width * known_image.height);
        double variance = compute_variance(known_image.data, known_image.width * known_image.height);

        known_image_hashes[known_index] = hashSHA256Image(&known_image);

        // Print the hash
        print_hash(known_image_hashes[known_index]);

        // // Print the stats
        printf(" %f", mean);
        // printf("mean: %f, var: %f", mean, variance);
        // printf("width: %d, height: %d", known_image.width, known_image.height);
        printf("\n");

        free(known_image.data);
    }
}

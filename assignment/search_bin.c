#include <stdio.h>
#include <stdbool.h>
#include "2071_image.h"
#include "2071_hash.h"
#include "2071_stats.h"
#include "2071_files.h"
#include "2071_sort.h"

// Adapted from https://stackoverflow.com/a/25966181
int lower_bound(float arr[], float key, int low, int high)
{
    if (low > high)
        // return -1;
        return low;

    int mid = low + ((high - low) >> 1);
    // if (arr[mid] == key) return mid;

    // Attention here, we go left for lower_bound when meeting equal values
    if (arr[mid] >= key)
        return lower_bound(arr, key, low, mid - 1);
    else
        return lower_bound(arr, key, mid + 1, high);
}
int upper_bound(float arr[], float key, int low, int high)
{
    if (low > high)
        // return -1;
        return low;

    int mid = low + ((high - low) >> 1);
    // if (arr[mid] == key) return mid;

    // Attention here, we go right for upper_bound when meeting equal values
    if (arr[mid] > key)
        return upper_bound(arr, key, low, mid - 1);
    else
        return upper_bound(arr, key, mid + 1, high);
}
// Find matching indices
void binary_search(float candidates[], float key, int candidates_length, int *lower_bound_result, int *upper_bound_result)
{
    int low = lower_bound(candidates, key, 0, candidates_length);
    int high = upper_bound(candidates, key, 0, candidates_length);

    *lower_bound_result = low;
    *upper_bound_result = high;

    return;
}

int find_match(uint8_t *unknown_hash, float unknown_mean, uint8_t **known_hashes, float *known_means, int known_hashes_length)
{
    int lower;
    int upper;
    
    binary_search(known_means, unknown_mean, known_hashes_length, &lower, &upper);
    int hashsize = sha256_desc.hashsize;

    // printf("%d %d\n", lower, upper);

    if (lower <= upper)
    {
        int matching_index = -1;
        for (int potential_match = lower; potential_match <= upper; potential_match++)
        {
            // Compare to the unknown hash, stop looping if equal
            uint8_t *known_hash = known_hashes[potential_match];
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
                matching_index = potential_match;
                break;
            }
        }
        return matching_index;
    }
    else
    {
        return -1;
    }
}

// Usage: search dataset_a/known dataset_a/unknown_no_transform hashes.txt
int main(int argc, char *argv[])
{
    int max_known_file_count = 1000;
    int max_filename_length = 100; // characters

    char **known_image_names = malloc(max_known_file_count * sizeof(char *)); // pointer to an array of filenames
    // Allocate space for filenames
    for (int hash_index = 0; hash_index < max_known_file_count; hash_index++)
    {
        known_image_names[hash_index] = malloc(max_filename_length + 1);
    }

    char **unknown_image_names;
    char *unknown_image_dir = argv[1];
    int unknown_images_length = store_filenames(unknown_image_dir, &unknown_image_names);
    uint8_t *known_image_hashes[max_known_file_count];
    float known_image_means[max_known_file_count];

    // Read in hashes of all known images
    char *hashes_filename = argv[2];
    FILE *hash_file = fopen(hashes_filename, "r");
    char raw_hash_string[100];
    char raw_file_string[max_filename_length];
    float mean_value;
    int hash_index = 0;

    while (fscanf(hash_file, "%s %s %f", known_image_names[hash_index], raw_hash_string, &mean_value) == 3)
    {
        known_image_means[hash_index] = mean_value;
        hash_string_to_array(&known_image_hashes[hash_index], raw_hash_string); // TODO: remove the need for this
        // printf("%s\n", raw_hash_string);
        // print_hash(known_image_hashes[hash_index]);
        hash_index++;
    }

    int known_hash_count = hash_index;

    // Make sure the hashes, means and filenames are in the correct order
    sort_by_key(known_image_hashes, known_image_means, known_hash_count);
    sort_by_key(known_image_names, known_image_means, known_hash_count);
    sort_simple(known_image_means, known_hash_count);

    // Compute hashes of all unknown images, and find the hash matches for the known images
    printf("unknown known\n");
    for (int unknown_index = 0; unknown_index < unknown_images_length; unknown_index++)
    {
        const char *unknown_image_filename = unknown_image_names[unknown_index];
        Image unknown_image = read_image_from_file(unknown_image_filename);
        float mean = compute_mean(unknown_image.data, unknown_image.width * unknown_image.height);

        unsigned char *unknown_hash = hashSHA256Image(&unknown_image);

        // Find and report match
        int match_index = find_match(unknown_hash, mean, known_image_hashes, known_image_means, known_hash_count);

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

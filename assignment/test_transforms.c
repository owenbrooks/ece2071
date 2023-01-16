#include "2071_image.h"
#include "2071_transform.h"

Image copy_image(Image *image)
{
    Image temp_image;
    temp_image.width = image->width;
    temp_image.height = image->height;
    temp_image.data = malloc(sizeof(int) * temp_image.width * temp_image.height);
    memcpy(temp_image.data, image->data, sizeof(int) * temp_image.width * temp_image.height); // copy the pixels
    return temp_image;
}

int main(void)
{
    Image image = read_image_from_file("dataset_a/known/known-000.jpg");
    printf("%d %d\n", image.height, image.width);
    Image orig = copy_image(&image);

    write_image_to_file("orig.jpg", &orig);

    image = copy_image(&orig);
    flip(&image);
    write_image_to_file("flipped.jpg", &image);

    image = copy_image(&orig);
    mirror(&image);
    write_image_to_file("mirrored.jpg", &image);

    image = copy_image(&orig);
    rot_90_clockwise(&image);
    write_image_to_file("rot90clock.jpg", &image);

    image = copy_image(&orig);
    rot_90_anticlockwise(&image);
    write_image_to_file("rot90anticlock.jpg", &image);
}
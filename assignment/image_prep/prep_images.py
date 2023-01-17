#!/usr/bin/env python
# Preparing dataset
# - Convert to greyscale if necessary
# - Crop to desired aspect ratio (square)
# - Resize to desired size (224x224)
# - Apply random transformation
# - Save with unique ID

from PIL import Image, ImageOps
import random
import os

def main():
    source_dir = "../dataset_b_raw"
    output_dir = "../dataset_b/known"

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    input_files = [file.path for file in os.scandir(source_dir) if file.is_file]
    input_files = input_files[:1000] # only use the first 1000 images (to make consistent between datasets)

    random.seed(2071)
    for (file_index, filename) in enumerate(input_files):
        im_orig = Image.open(filename)
        im_prepared = prepare_image(im_orig)
        im_final = transform_image(im_prepared)

        output_name = f"known-{file_index:03}.png"
        output_path = os.path.join(output_dir, output_name)
        im_final.save(output_path)

        print(f"{file_index+1}/{len(input_files)}")


def prepare_image(im_orig):
    im_greyscale = im_orig.convert('L')
    im_cropped = crop_to_square(im_greyscale)
    im_resized = im_cropped.resize((224, 224))
    return im_resized


def transform_image(im):
    # Randomly apply a few transformations
    im_transformed = im.copy()
    possible_transformations = [rot90anticlock, rot90clock, flip, mirror]
    number_of_transformations = 3
    for _ in range(number_of_transformations):
        random_number = random.randint(0, len(possible_transformations)-1) # generation is inclusive of the end-points
        random_transform = possible_transformations[random_number]
        im_transformed = random_transform(im_transformed)

    return im_transformed


# Image transformations
def rot90anticlock(image):
    return image.rotate(90)
def rot90clock(image):
    return image.rotate(-90)
def flip(image):
    # Flips upside-down
    return ImageOps.flip(image)
def mirror(image):
    # Mirrors image left to right
    return ImageOps.mirror(image)

# Shift / rot


def crop_to_square(image):
    new_height = min(image.height, image.width)
    new_width = new_height

    left=image.width/2-new_width/2
    top=image.height/2-new_height/2
    right=image.width/2+new_width/2
    bottom=image.height/2+new_height/2

    cropped = image.crop((left, top, right, bottom))

    return cropped

if __name__ == "__main__":
    main()
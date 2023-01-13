#!/usr/bin/env python
# - Randomly choose X images to be unknown set
# - Randomly apply transformations to these
# - Save these

from PIL import Image
import random
import os
from prep_images import transform_image
import csv

def main():
    random.seed(2071)

    dataset_dir = "../dataset_b"
    mystery_set_size = 10

    known_dir = os.path.join(dataset_dir, 'known')
    variants = ['no_transform', 'transformed']
    
    for variant in variants:
        output_dir = os.path.join(dataset_dir, f'unknown_{variant}')

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        input_files = [file.path for file in os.scandir(known_dir) if file.is_file]

        mystery_files = random.sample(input_files, mystery_set_size)

        # Transform and save new files
        for (file_index, filename) in enumerate(mystery_files):
            im_orig = Image.open(filename)

            if variant == "transformed":
                im_final = transform_image(im_orig)
            else:
                im_final = im_orig

            output_name = f"unknown-{variant}-{file_index:03}.jpg"
            output_path = os.path.join(output_dir, output_name)
            im_final.save(output_path)

            print(f"{file_index+1}/{len(mystery_files)}")

        # Create and save answer key
        anwser_key_filename = f"{os.path.split(dataset_dir)[-1]}_{variant}_answers.csv"
        with open(anwser_key_filename, mode="w") as answer_key_file:
            answer_writer = csv.DictWriter(answer_key_file, delimiter=' ', fieldnames=['unknown', 'known'])
            answer_writer.writeheader()

            for (file_index, known_path) in enumerate(mystery_files):
                mystery_filename = f"unknown-{file_index:03}.jpg"
                known_filename = os.path.split(known_path)[-1]
                row = {"unknown": mystery_filename, "known": known_filename}
                answer_writer.writerow(row)


if __name__ == "__main__":
    main()
#!/usr/bin/env python
import sys
import csv
import os

""" Usage: python check_results.py dataset_a_no_transform_answers.csv results.txt """

def main(anwser_key_filename, assignment_output_filename):
    false_positive_count = 0
    correct_count = 0

    with open(anwser_key_filename, mode="r") as answer_key_file:
        answer_reader = csv.DictReader(answer_key_file, delimiter=' ')

        with open(assignment_output_filename, mode="r") as assignment_output_file:
            results_reader = csv.DictReader(assignment_output_file, delimiter=' ')

            answer_rows = [row for row in answer_reader]
            total_unknown_file_count = len(answer_rows)

            for row in results_reader:
                known_filename = os.path.basename(row['known']) # extract only the final filename
                # e.g. dataset_a/known/known-243.png becomes known-243.png
                unknown_filename = os.path.basename(row['unknown'])

                sanitised_row = {'unknown': unknown_filename, 'known': known_filename}
                if sanitised_row in answer_rows:
                    correct_count += 1
                else:
                    false_positive_count += 1

            print(f"{correct_count}/{total_unknown_file_count} correct.")
            print(f"{false_positive_count}/{total_unknown_file_count} false positives.")


if __name__ == "__main__":
    anwser_key_filename = sys.argv[1]
    assignment_output_filename = sys.argv[2]
    main(anwser_key_filename, assignment_output_filename)
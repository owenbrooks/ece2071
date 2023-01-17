
# make
TIME=$({ time ./output/stats dataset_a/known dataset_a/unknown_no_transform > output/hashes.txt ; } 2>&1 >/dev/null)

TIMEFORMAT='%3R'
TIME=$({ time ./output/search dataset_a/known dataset_a/unknown_no_transform output/hashes.txt > output/results.txt ; } 2>&1 >/dev/null)
python3 check_results.py image_prep/dataset_a_no_transform_answers.csv output/results.txt
echo "Took $TIME seconds"
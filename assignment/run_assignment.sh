
# make
# TIME=$({ time ./stats dataset_a/known dataset_a/unknown_no_transform > hashes.txt ; } 2>&1 >/dev/null)

TIMEFORMAT='%3R'
TIME=$({ time ./search dataset_a/known dataset_a/unknown_no_transform > results.txt ; } 2>&1 >/dev/null)
python3 check_results.py image_prep/dataset_a_no_transform_answers.csv results.txt
echo "Took $TIME seconds"
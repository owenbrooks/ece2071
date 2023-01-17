
# make
TIMEFORMAT='%3R'

# stats output is redirected to hashes.txt. stdout of time is ignored, but stderr of time is redirected to stdout out which is stored in STATS_TIME variable
STATS_TIME=$({ time ./output/stats dataset_a/known dataset_a/unknown_no_transform > output/hashes.txt ; } 2>&1 >/dev/null)
# SEARCH_TIME=$({ time ./output/search_lin dataset_a/known dataset_a/unknown_no_transform output/hashes_old.txt > output/matches.txt ; } 2>&1 >/dev/null)
SEARCH_TIME=$({ time ./output/search_bin dataset_a/unknown_no_transform output/hashes.txt > output/matches.txt ; } 2>&1 >/dev/null)
python3 check_matches.py image_prep/dataset_a_no_transform_answers.csv output/matches.txt
echo "Stats took $STATS_TIME seconds."
echo "Search took $SEARCH_TIME seconds."
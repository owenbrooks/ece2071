image_stats:
	gcc -o stats output/stats.c `pkg-config --cflags --libs MagickWand`

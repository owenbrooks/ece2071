stats:
	gcc -o stats output/stats.c `pkg-config --cflags --libs MagickWand`
hash:
	gcc hash.c -o output/hash -I /opt/homebrew/include -ltomcrypt -L /opt/homebrew/lib
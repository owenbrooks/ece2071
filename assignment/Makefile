
BUILDDIR=output
CFLAGS=-Iinclude -lm -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include -ltcmalloc
# -ltomcrypt provides hashing functions
# -lm is math, needed for tomcrypt
# -ltcmalloc for gperftools
.PHONY: stats search

stats:
	mkdir -p $(BUILDDIR)
	gcc stats.c -o $(BUILDDIR)/stats $(CFLAGS)
search:
	mkdir -p $(BUILDDIR)
	gcc search.c -o $(BUILDDIR)/search $(CFLAGS)
stbi:
	mkdir -p $(BUILDDIR)
	gcc stb_image_example.c -o $(BUILDDIR)/stbi_image_example $(CFLAGS)
tf:
	mkdir -p $(BUILDDIR)
	gcc test_transforms.c -g -o $(BUILDDIR)/test_transforms $(CFLAGS)

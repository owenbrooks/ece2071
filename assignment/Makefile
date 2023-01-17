
BUILDDIR=output
CFLAGS=-Iinclude -lm -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include -ltcmalloc
# -ltomcrypt provides hashing functions
# -lm is math, needed for tomcrypt
# -ltcmalloc for gperftools
.PHONY: stats search all

all: stats search tf

stats:
	mkdir -p $(BUILDDIR)
	gcc stats.c -o $(BUILDDIR)/stats $(CFLAGS)
search:
	mkdir -p $(BUILDDIR)
	gcc search.c -o $(BUILDDIR)/search $(CFLAGS)
tf:
	mkdir -p $(BUILDDIR)
	gcc test_transforms.c -g -o $(BUILDDIR)/test_transforms $(CFLAGS)

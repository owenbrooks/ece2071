
BUILDDIR=output
CFLAGS=-Iinclude -lm -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include -ltcmalloc
# -ltomcrypt provides hashing functions
# -lm is math, needed for tomcrypt
# -ltcmalloc for gperftools
.PHONY: stats search all

all: stats search_bin tf

stats:
	mkdir -p $(BUILDDIR)
	gcc stats.c -o $(BUILDDIR)/stats $(CFLAGS)
# search_lin:
# 	mkdir -p $(BUILDDIR)
# 	gcc search_lin.c -o $(BUILDDIR)/search $(CFLAGS)
search_bin:
	mkdir -p $(BUILDDIR)
	gcc search_bin.c -o $(BUILDDIR)/search $(CFLAGS)
tf:
	mkdir -p $(BUILDDIR)
	gcc test_transforms.c -g -o $(BUILDDIR)/test_transforms $(CFLAGS)

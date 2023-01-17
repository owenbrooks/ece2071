
BUILDDIR=output
CFLAGS=-Iinclude -lm -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include -ltcmalloc
# -ltomcrypt provides hashing functions
# -lm is math, needed for tomcrypt
# -ltcmalloc for gperftools
.PHONY: stats search all sort

all: stats search_bin search_lin tf

stats:
	mkdir -p $(BUILDDIR)
	gcc stats.c -o $(BUILDDIR)/stats $(CFLAGS)
search_lin:
	mkdir -p $(BUILDDIR)
	gcc search_lin.c -o $(BUILDDIR)/search_lin $(CFLAGS)
search_bin:
	mkdir -p $(BUILDDIR)
	gcc search_bin.c -g -o $(BUILDDIR)/search_bin $(CFLAGS)
tf:
	mkdir -p $(BUILDDIR)
	gcc test_transforms.c -g -o $(BUILDDIR)/test_transforms $(CFLAGS)
sort:
	gcc sort.c -Iinclude -o sort && ./sort
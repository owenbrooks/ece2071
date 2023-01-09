
BUILDDIR=output

assignment:
	mkdir -p $(BUILDDIR)
	gcc assignment.c -Iinclude -o $(BUILDDIR)/assignment `pkg-config --cflags --libs MagickWand` -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include

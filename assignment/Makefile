
BUILDDIR=output
CFLAGS=-Iinclude -ltomcrypt -L /opt/homebrew/lib -I /opt/homebrew/include

assignment:
	mkdir -p $(BUILDDIR)
	gcc assignment.c -g -o $(BUILDDIR)/assignment $(CFLAGS)
stbi:
	mkdir -p $(BUILDDIR)
	gcc stb_image_example.c -o $(BUILDDIR)/stbi_image_example $(CFLAGS)
tf:
	mkdir -p $(BUILDDIR)
	gcc test_transforms.c -g -o $(BUILDDIR)/test_transforms $(CFLAGS)

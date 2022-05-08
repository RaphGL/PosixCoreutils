CC=gcc
CFLAGS=-std=c11

all: echo mv true cat wc basename dirname cmp head

echo: src/echo.c
mv: src/mv.c
true: src/true.c
cat: src/cat.c
wc: src/wc.c
basename: src/basename.c
dirname: src/dirname.c
cmp: src/cmp.c
head: src/head.c

echo mv true cat wc basename cmp head:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

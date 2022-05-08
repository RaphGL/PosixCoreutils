CC=gcc
CFLAGS=-std=c11

all: echo mv true cat wc basename dirname cmp head false tee

echo: src/echo.c
mv: src/mv.c
true: src/true.c
cat: src/cat.c
wc: src/wc.c
basename: src/basename.c
dirname: src/dirname.c
cmp: src/cmp.c
head: src/head.c
false: src/false.c
tee: src/tee.c

echo mv true cat wc basename cmp head false tee:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

CC=gcc
CFLAGS=-std=c11

all: echo mv true cat wc basename dirname

echo: src/echo.c
mv: src/mv.c
true: src/true.c
cat: src/cat.c
wc: src/wc.c
basename: src/basename.c
dirname: src/dirname.c

echo mv true cat wc basename:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

CC=gcc
CFLAGS=-std=c11

all: echo mv true cat wc basename dirname cp

echo: src/echo.c
mv: src/mv.c
true: src/true.c
cat: src/cat.c
wc: src/wc.c
basename: src/basename.c
dirname: src/dirname.c
cp: src/cp.c

echo mv true cat wc basename cp:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

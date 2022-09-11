CC=gcc
CFLAGS=-std=c11 -Wall

PROGRAMS=expand

all: echo mv true cat wc basename dirname cmp head false tee kill mkdir

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
kill: src/kill.c
mkdir: src/mkdir.c
expand: src/expand.c


$(PROGRAMS):
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

clean:
	rm -rf build/
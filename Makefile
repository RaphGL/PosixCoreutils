CC=gcc
CFLAGS=-std=c11

all: echo mv dirname cat

echo: src/echo.c
mv: src/mv.c
true: src/true.c
cat: src/cat.c

echo mv true cat:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

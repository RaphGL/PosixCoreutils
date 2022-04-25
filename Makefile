CC=gcc
CFLAGS=-std=c11

all: echo mv

echo: src/echo.c
mv: src/mv.c

echo mv:
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o build/$@ 

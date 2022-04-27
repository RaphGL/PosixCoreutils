#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    FILE *file;
    char byte;

    while (opt = getopt(argc, argv, "uh") != -1)
    {
        if (opt == 'h')
        {
        }
    }

    for (; optind < argc; optind++)
    {
        file = fopen(argv[optind], "r");
        while ((byte = fgetc(file)) != EOF)
        {
            putc(byte, stdout);
        }
    }
    fclose(file);
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: cat [OPTION]... [FILE]...\n\
    Concatenate FILE(s) to standard output.\n\n\
    -u\t\tignored\n\
    -h\t\tShow this message");
}
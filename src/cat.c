#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int opt;
    FILE *file;
    char byte;

    while (opt = getopt(argc, argv, "u") != -1)
    {
        if (opt == 'u')
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

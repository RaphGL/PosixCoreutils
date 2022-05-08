#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    int n = 10;
    while ((opt = getopt(argc, argv, "n:h")) != -1)
    {
        switch (opt)
        {
        case 'n':
            n = atoi(optarg);
            break;
        case 'h':
            show_usage();
            break;
        }
    }

    for (; optind < argc; optind++)
    {
        FILE *fd = fopen(argv[optind], "r");
        if (fd != NULL)
        {
            int c;
            int newline = 0;
            while ((c = fgetc(fd)) != EOF)
            {
                fputc(c, stdout);
                if (c == '\n')
                {
                    newline++;
                }
                if (newline == n)
                {
                    break;
                }
            }
            fclose(fd);
        }
    }
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: head [OPTION]... [FILE]...\n\
    Print the first 10 lines of each FILE to standard output.\n\n\
    -n\t\tprint n number of lines\n\
    -h\t\tshow this message");
}
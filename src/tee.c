#include <stdio.h>
#include <getopt.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "iha")) != -1)
    {
        switch (opt)
        {
        case 'a':
            break;
        case 'i':
            break;
        case 'h':
            show_usage();
            return;
            break;
        }
    }

    char in[256];
    FILE *fd = NULL;
    fgets(in, sizeof(in), stdin);
    for (; optind < argc; optind++)
    {
        if (argc > 1)
            fd = fopen(argv[optind], "w");
        for (int i = 0; in[i] != NULL; i++)
        {
            if (fd != NULL)
                fputc(in[i], fd);
            fputc(in[i], stdout);
        }
    }
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: tee [OPTION]... [FILE]...\n\
    Copy standard input to each FILE, and also to standard output.\n\n\
    -a\t\tappend to the given FILEs, do not overwrite\n\
    -i\t\tignore interrupts\n\
    -h\t\tshow this message");
}
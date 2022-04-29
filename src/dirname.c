#include <stdio.h>
#include <string.h>
#include <getopt.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1)
    {
        if (opt = 'h')
        {
            show_usage();
        }
    }
    for (; optind < argc; optind++)
    {
        char *slash = strrchr(argv[optind], '/');
        int slash_index = slash - argv[optind];
        if (slash_index == strlen(argv[optind]) - 1)
        {
            argv[optind][slash_index] = '\n';
            slash = strrchr(argv[optind], '/');
            slash_index = slash - argv[optind];
        }
        for (int j = 0; j < slash_index; j++)
        {
            putc(argv[optind][j], stdout);
        }
        putc('\n', stdout);
    }
    return 0;
}

void show_usage(void)
{
    puts("Usage: dirname [OPTION] NAME...\n\
Output each NAME with its last non-slash component and trailing slashes");
}
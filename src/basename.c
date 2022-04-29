#include <stdio.h>
#include <string.h>
#include <getopt.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1)
    {
        if (opt == 'h')
        {
            show_usage();
        }
    }

    char *basename;
    for (; optind < argc; optind++)
    {
        // get location to last '/'
        basename = strrchr(argv[optind], '/');
        if (basename != NULL)
        {
            // go to after '/'
            basename++;
            puts(basename);
        }
    }
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: basename [OPTION]... [NAME]...\n\
    Print NAME with leading directory components removed.");
}
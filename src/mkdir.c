#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "hmp")) != -1)
    {
        switch (opt)
        {
        case 'h':
            show_usage();
            break;
        case 'm':
            break;
        case 'p':
            break;
        }
    }

    for (; optind < argc; optind++)
    {
        mkdir(argv[optind], S_IRWXU | S_IRWXG | S_IRWXU);
    }
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: mkdir [OPTION]... DIRECTORY\n\
    Create the DIRECTORY(ies), if they do not already exist.\n\n\
    -m\t\tset file mode (as in chmod)\n\
    -i\t\tno error if existing, make parent directories as needed, \n\
    \t\t\twith their file modes unaffected by any -m option.");
}
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>

void show_usage(void);

void main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "fHiLPpRh")) != -1)
    {
        switch (opt)
        {
        case 'f':
            break;
        case 'H':
            break;
        case 'i':
            break;
        case 'L':
            break;
        case 'P':
            break;
        case 'p':
            break;
        case 'R':
            break;
        case 'h':
            break;
        }
    }
    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: cp [OPTION]... SOURCE DEST\n\
    Usage: cp [OPTION]... SOURCE... DIRECTORY\n\
    Copy SOURCE to DEST or multiple SOURCEs to DIRECTORY\n\n\
    -f\t\tif the destination file exists, overwrite it\n\
    -H\t\tTODO\n\
    -i\t\tprompt before overwriting\n\
    -L\t\tTODO\n\
    -P\t\t\tTODOn\
    -p\t\tcopy preserving permissions, date data, UID and GID\n\
    -R\t\tcopy directories recursively\n\
    -h\t\tshow this message");
}
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

void show_usage();
void move_file(char *src, char *target);

int main(int argc, char **argv)
{
    int opt;
    bool interactive = false;
    bool force = false;

    while ((opt = getopt(argc, argv, "ifh")) != -1)
    {
        switch (opt)
        {
        case 'i':
            interactive = true;
            break;
        case 'f':
            force = true;
            break;
        case 'h':
            show_usage();
            break;
        }
    }

    for (; optind < argc - 1; optind++)
    {
        if (force)
        {
            goto moving_file;
        }
        // check is file exists
        if (interactive && access(argv[optind], F_OK) == 0)
        {
            char ans[4096];
            printf("mv: overwrite '%s'?", argv[argc - 1]);
            scanf("%s", ans);
            if (strcmp(ans, "y") == 0 || strcmp(ans, "yes") == 0)
            {
                goto moving_file;
            }
        }
    moving_file:
        move_file(argv[optind], argv[argc - 1]);
    }
    return 0;
}

void move_file(char *src, char *target)
{
    struct stat file;
    char *srcpath = NULL;
    char *targetpath;

    // if src has subfolders, get the basename
    char *path = strrchr(src, '/');
    if (path != NULL)
    {
        path += 1;
        srcpath = path;
    }
    else
    {
        srcpath = src;
    }

    // if target is a folder, create path from inside of it
    if (stat(target, &file) == 0 && S_ISDIR(file.st_mode))
    {
        sprintf(targetpath, "%s/%s", target, srcpath);
    }
    else
    {
        targetpath = target;
    }
    rename(src, targetpath);
}

void show_usage()
{
    puts("\
    Usage: mv [OPTION]... SOURCE DEST\n\
    Rename SOURCE to DEST\n\n\
    -f\t\tdo not prompt before overwriting\n\
    -i\t\tprompt before overwrite");
}
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

    while ((opt = getopt(argc, argv, "if")) != -1)
    {
        switch (opt)
        {
        case 'i':
        interactive = true;
            break;
        case 'f':
        force = true;
            break;
        }
    }

    for (; optind < argc - 1; optind++)
    {
        if (force)
        {
            goto moving_file;
        }
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
    char *targetpath = NULL;
    if (stat(target, &file) == 0 && S_ISDIR(file.st_mode))
    {
        sprintf("%s/%s", targetpath, target, src);
    }
    else
    {
        targetpath = target;
    }
    rename(src, targetpath);
}
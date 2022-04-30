#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

void show_usage(void);
int handle_dirs(int optind, int argc, char **argv, struct stat *src_info, struct stat *tg_info);
handle_reg_files(int optind, char **argc, struct stat *src_info, struct stat *tg_info);
void fcopy(char *dest, char *filename);

bool force = false;
bool interactive = false;
bool follow_symlinks = false;
bool recursive = false;
bool preserve_perms = false;

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "fHiLPpRh")) != -1)
    {
        switch (opt)
        {
        case 'f':
            force = true;
            break;
        case 'H':
            break;
        case 'i':
            interactive = true;
            break;
        case 'L':
            follow_symlinks = true;
            break;
        case 'P':
            break;
        case 'p':
            preserve_perms = true;
            break;
        case 'R':
            recursive = true;
            break;
        case 'h':
            break;
        }
    }

    struct stat src_info;
    struct stat tg_info;
    // open or create file for target
    FILE *target = fopen(argv[argc - 1], "w");
    for (; optind < argc - 1; optind++)
    {
        // checks whether source and target are equal, if so writes to stderr and continues
        if (strcmp(argv[optind], argv[argc - 1]) != 0)
        {
            fprintf(stderr, "%s and %s are identical.", argv[optind], argv[argc - 1]);
            continue;
        }
        else
        {
            // open source if exists
            stat(argv[optind], &src_info);

            // check if source is a dir
            if (S_ISDIR(src_info.st_mode))
            {
                if (handle_dirs(optind, argc, argv, &src_info, &tg_info) != 0)
                {
                    continue;
                }
            } else if (S_ISREG(src_info.st_mode))
            {
                if (handle_reg_files(optind, argc, &src_info, &tg_info) != 0)
                {
                    continue;
                }
            }
        }
    }
    fclose(target);
    return 0;
}

void fcopy(char *dest, char *filename)
{
    int c;
    FILE *src = fopen(filename, "r");
    if (src != NULL)
    {
        while ((c = fgetc(src)) != EOF)
        {
            fputc(c, dest);
        }
    }
    fclose(src);
}

handle_reg_files(int optind, char **argc, struct stat *src_info, struct stat *tg_info)
{
    // TODO
}

int handle_dirs(int optind, int argc, char **argv, struct stat *src_info, struct stat *tg_info)
{
    // if -R is not given go to next source file
    if (!recursive)
    {
        fputs("SOURCE is a directory.", stderr);
        return 1;
    }
    // if . or .. is used, skip it
    if (strcmp(argv[optind], ".") == 0 || strcmp(argv[optind]) == 0)
    {
        return 2;
    }
    stat(argv[argc - 1], tg_info);
    // if target is not a directory, skip src
    if (!S_ISDIR(tg_info->st_mode))
    {
        fprintf(stderr, "%s is not a directory.", argv[argc - 1]);
        return 3;
    }
    // if target doesn't exist create it
    // make the target have the same permissions as source
    if (access(argv[argc - 1], F_OK) == -1)
    {
        if (mkdir(argv[argc - 1], src_info->st_mode) != 0)
        {
            fprintf(stderr, "Could not create %s", argv[argc - 1]);
            return 4;
        }
    }
    // if -p is not set, copy source perms to target
    else if (!preserve_perms)
    {
        chmod(argv[argc - 1], src_info->st_mode);
    }

    DIR *src_dir = opendir(argv[optind]);
    struct dirent *src_entry;
    if (src_dir != NULL)
    {
        char *dest;
        while ((src_entry = readdir(src_dir)) != NULL)
        {
            sprintf(dest, "%s/%s", argv[argc - 1], argv[optind]);
            fcopy(dest, argv[optind]);
        }
        closedir(src_dir);
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
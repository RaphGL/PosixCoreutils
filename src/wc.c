#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include<ctype.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    bool count_bytes = false;
    bool count_newlines = false;
    bool count_chars = false;
    bool count_words = false;

    while ((opt = getopt(argc, argv, "clmwh")) != -1)
    {

        switch (opt)
        {
        case 'c':
            count_bytes = true;
            break;
        case 'l':
            count_newlines = true;
            break;
        case 'm':
            count_chars = true;
            break;
        case 'w':
            count_words = true;
            break;
        case 'h':
            show_usage();
            break;
        }
    }

    FILE *file;
    char cur;
    char prev = '+';
    struct stat fstat;
    int nbytes = 0;
    int nnewlines = 0;
    int nchars = 0;
    int nwords = 0;
    for (; optind < argc; optind++)
    {
        if (stat(argv[optind], &fstat) != -1)
        {
            nbytes = fstat.st_size;
        }

        file = fopen(argv[optind], "r");
        while ((cur = fgetc(file)) != EOF)
        {
            if (cur == '\n')
            {
                nnewlines++;
            }
            if (cur == '\n' || cur == ' ' || cur == '\t' && isalpha(prev))
            {
                nwords++;
                prev = cur;
            }
            nchars++;
            prev = cur;
        }

        if (!count_newlines && !count_words && !count_chars && !count_bytes)
        {
            printf("%d %d %d %s\n", nnewlines, nwords, nchars, argv[optind]);
        }
        else
        {
            if (count_newlines)
            {
                printf("%d ", nnewlines);
            }
            if (count_words)
            {
                printf("%d ", nwords);
            }
            if (count_chars)
            {
                printf("%d ", nchars);
            }
            if (count_bytes)
            {
                printf("%d ", nbytes);
            }
            puts(argv[optind]);
        }

        fclose(file);
        nbytes = 0;
        nchars = 0;
        nnewlines = 0;
        nwords = 0;
    }

    return 0;
}

void show_usage(void)
{
    puts("\
    Usage: wc [OPTION]... [FILE]...\n\
    Print newline, word, and byte counts for each FILE, and a total line if\
more than one FILE is specified. A word is a non-zero-length sequence of \
characters delimited by white space.\n\n\
    -c\t\tprint the byte counts\n\
    -m\t\tprint the character counts\n\
    -l\t\tprint the newline counts\n\
    -w\t\tprint the word counts\n\
    -h\t\tshow this message");
}


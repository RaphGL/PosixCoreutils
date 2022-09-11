#include <getopt.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char expanded[BUFSIZ];
char *expandln(char *string, int tablist);

int main(int argc, char **argv)
{
    int opt;
    int tablist = 8;
    while ((opt = getopt(argc, argv, "ht:")) != -1)
    {
        switch (opt)
        {
        case 't':
            tablist = atoi(optarg);
            break;
        case 'h':
            break;
        }
    }

    if (argc != optind)
    {

        for (; optind < argc; optind++)
        {
            if (access(argv[optind], F_OK) == 0)
            {
                FILE *fp = fopen(argv[optind], "r");
                if (fp == NULL)
                    exit(EXIT_FAILURE);

                char fp_string[1024];
                while (fgets(fp_string, 1024, fp))
                {
                    printf(expandln(fp_string, tablist));
                }
                fclose(fp);
            }
        }
    }
    // Piped expand
    else
    {
        char pipe_string[BUFSIZ];
        while (fgets(pipe_string, 1024, stdin))
        {
            printf(expandln(pipe_string, tablist));
        }
    }
    return 0;
}

char *expandln(char *string, int tablist)
{
    int expanded_i = 0;
    for (int i = 0; i <= strlen(string); i++)
    {
        if (string[i] == ' ')
        {
            for (int j = 0; j < tablist; j++)
            {
                expanded[expanded_i] = '\t';
                expanded_i++;
            }
        }
        else
        {
            expanded[expanded_i] = string[i];
            expanded_i++;
        }
    }
    return expanded;
}
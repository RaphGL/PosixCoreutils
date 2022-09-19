#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void show_usage(void);

int main(int argc, char **argv)
{
    int opt;
    // TODO implement flags
    char *eof_str; // -E
    char *repl_str; // -l
    int max_lines; // -L
    int max_args; // -n
    int max_chars; // -s
    bool verbose; // -t
    bool prompt_user; // -p

    while ((opt = getopt(argc, argv, "hE:l:n:ps:tx")) == 0)
    {
        switch (opt)
        {
        case 'h':
            break;
        default:
            puts("Error: Argument not recognized.");
            break;
        }
    }

    char *util = argv[optind];
    char pipe_str[BUFSIZ];
    char cmd_str[1024];
    fgets(pipe_str, BUFSIZ, stdin);
    strcat(cmd_str, util);
    for (optind++; optind < argc; optind++)
    {
        strcat(cmd_str, " ");
        strcat(cmd_str, argv[optind]);
    }
    strcat(cmd_str, " ");
    strcat(cmd_str, pipe_str);
    system(cmd_str);

    return 0;
}
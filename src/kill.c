#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    int opt;
    char signame[10];
    bool all_signals = false;
    while ((opt = getopt(argc, argv, "ls:")) != -1)
    {
        switch (opt)
        {
        case 'l':
            all_signals = true;
            break;
        case 's':
            char c[10];
            memcpy(c, optarg, 10);
            for (int i = 0; i < 10; i++)
            {
                c[i] = toupper(c[i]);
            }
            memcpy(signame, c, 10);
            break;
        }
    }

    int sigid = 0;
    if (strstr(signame, "SIGHUP") != NULL)
        sigid = SIGHUP;
    else if (strstr(signame, "SIGINT") != NULL)
        sigid = SIGINT;
    else if (strstr(signame, "SIGQUIT") != NULL)
        sigid = SIGQUIT;
    else if (strstr(signame, "SIGABRT") != NULL)
        sigid = SIGABRT;
    else if (strstr(signame, "SIGKILL") != NULL)
        sigid = SIGKILL;
    else if (strstr(signame, "SIGALRM") != NULL)
        sigid = SIGALRM;
    else if (strstr(signame, "SIGTERM") != NULL)
        sigid = SIGTERM;

    for (; optind < argc; optind++)
    {
        kill((atoi(argv[optind])), sigid);
    }
    return 0;
}
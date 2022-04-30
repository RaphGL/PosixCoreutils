#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

void show_usage(void);

int main(int argc, char **argv)
{
	int opt;
	bool status_only = false;
	while ((opt = getopt(argc, argv, "lsh")) != -1)
	{
		switch (opt)
		{
		case 'l':
			// TODO
			break;
		case 's':
			status_only = true;
			break;
		case 'h':
			break;
		}
	}

	FILE *f1 = fopen(argv[optind], "r");
	FILE *f2 = fopen(argv[optind + 1], "r");
	if (f1 == NULL || f2 == NULL)
	{
		if (!status_only)
			fprintf(stderr, "cmp: %s%s: No such file or directory\n", argv[optind], argv[optind + 1]);
		return 2;
	}

	int a;
	int b;

	while (a != EOF && b != EOF)
	{
		a = fgetc(f1);
		b = fgetc(f2);
		if (a != b)
		{
			return 1;
		}
	}

	fclose(f1);
	fclose(f2);
	return 0;
}

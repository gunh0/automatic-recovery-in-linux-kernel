#include <stdio.h>

int main(int argc, char **argv)
{
	printf("argument count is %d\n", argc);

	int i = 0;
	printf("arugment list\n");
	for (i = 0; i < argc; i++)
	{
		printf("<%d>: %s\n", i, argv[i]);
	}
	return 0;
}
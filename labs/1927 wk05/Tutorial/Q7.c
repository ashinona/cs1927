// Read numbers from stdin; print their sum on stdout

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int n;   // current value
	int sum = 0; // sum of values //originally sum was not initialised, hence there was a random value inside
    

	while (scanf("%d",&n) == 1)
		sum += n;
	printf("%d\n", sum);
	return EXIT_SUCCESS;
}

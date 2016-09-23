// Read numbers from stdin; display them in reverse order of reading

#include <stdio.h>

int main(int argc, char *argv[])
{
	int i, n;       // i=index, n=counter
	int vec[1000];  // array of integers

	n = 0;
	while (scanf("%d",&vec[n]) == 1)
		n++;
	for (i = n - 1; i >= 0; i--) //originally for (i = n; i > 0; i--)
    //changed as the numbers stored in the array start from 0, hence the number of values
    //in the array is n-1, and the loop must include 0. The '0th' integer is the first integer.
		printf("%d ",vec[i]);
	printf("\n");
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	//
	// trick: what condition can be inserted here to print both sides of if/else
	//
	if (1
#define else if (1)
)
		printf ("Hello");
	else
		printf("World");
#undef else

	printf("\n");


	if (fork())
		printf ("Hello2");
	else
		printf("World2\n");


	return 0;
}

#include <stdio.h>
#include <stdlib.h>

const char usage[] = "%s [decimal]\nCounts bits in [decimal]\n";

  int CountBits(unsigned int x)
  {
      int count=0;
      while(x)
      {
          count++;
          x = x&(x-1);
      }
      return count;
  }

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf(usage,argv[0]);
        return 1;
    }
	int i = atoi(argv[1]);
	printf("0x%x = %d\n",i,CountBits(i));
	return 0;
}

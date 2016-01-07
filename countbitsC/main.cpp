#include <stdio.h>
#include <stdlib.h>

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
	int i = atoi(argv[1]);
	printf("0x%x = %d\n",i,CountBits(i));
	return 0;
}

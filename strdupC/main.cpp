#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<setjmp.h>

const char* usage = "USAGE: %0 [word #1] [word #2]\n";

char* my_strdup(const char* str)
{
	if (!str) return NULL;
	char* ret = (char*)malloc(sizeof(char) * strlen(str));
	strcpy(ret,str);
	return ret;
}

int main(int argc, char* argv[])
{
    char *s;
    s = my_strdup("Ok, starting up...");
    printf("%s\n", s);
    //getchar();
    free(s);

    // check for isomorphic
	if (argc < 3)
	{
		printf(usage,argv[0]);
		return 1;
	}

    char gg[128];
    strcpy(gg,argv[1]);
    strcat(gg,argv[1]);
    if (strstr(gg,argv[2]))
	printf("Those words are shifted from each other\n");
    else
	printf("Those words are NOT shifted from each other\n");

#if 0
	jmp_buf env;
	int i;
	int cnt = 0;
	
	i=setjmp(env);
	printf("i= %d\n",i);
	if(i==0)
		printf("I am in if ..\n");
	else{
		printf("I am in else too...\n");
		if (cnt++ > 10)
			exit(0);
	}
	longjmp(env,2);
	printf("Grrr... why am i not getting printed\n");
#endif

    return 0;
}

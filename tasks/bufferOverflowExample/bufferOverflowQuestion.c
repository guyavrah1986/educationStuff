#include <stdio.h>

void main(int argc, char *argv[])
{
	int flag = 0;
	char passwd[10];

	printf("buffer over flow - start \n");
	printf("buffer over flow - address of the LAST byte of the passwd array is:%p , the address of the flag (int) local variable is:%p the difference (in bytes) is:%d \n", &passwd[9], &flag, (char*)&passwd[9] - (char*)&flag);

	memset(passwd,0,sizeof(passwd));

	strcpy(passwd, argv[1]);

	if(0 == strcmp("LinuxGeek", passwd))
	{
		flag = 1;
	}

	if(flag)
	{
		printf("\n Password cracked \n");
	}
	else
	{
		printf("\n Incorrect passwd \n");
	}
	    
	return 0;
}

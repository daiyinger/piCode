#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void handler()
{
	printf("hello\n");
}
void main()
{
	int i;
	signal(SIGALRM,handler);
	alarm(5);	//5S
	for(i=1;i<7;i++)
	{
		printf("sleep %d ...\n",i);
		sleep(1);
		}
}

#include <stdio.h>
#include <stdlib.h>
void Delay(int i)
{
	volatile int j;
	for(j=0;j<i;j++);
}
int main(void)
{
	int i=0;
	while(i < 100)
	{
		
		usleep(1);
		Delay(5000);
		i++;	
	}
	return 0;
}

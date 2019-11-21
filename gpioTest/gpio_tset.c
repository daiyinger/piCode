#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd = 0;
	int delay_time_on = 6000;
	int delay_time_off = 100*1000;
	int delay_time_off1 = 0;
	int delay_time_on1 = 0;
	int cnt = 0;
	printf("hello\n");
	usleep(1000);
	if(argc > 1)
	{
		delay_time_on = atoi(argv[1]);
	}
	if(argc > 2)
	{
		delay_time_off = atoi(argv[2]);
	}
	if(argc > 3)
	{
		delay_time_on1 = atoi(argv[3]);
	}
	if(argc > 4)
	{
		delay_time_off1 = atoi(argv[4]);
	}
	printf("delay_time_on %d ms delay_time_off %d us delay_time_on1: %d ms delay_time_off1:%d us\n",
		delay_time_on, delay_time_off, delay_time_on1, delay_time_off1);
	fd = open("/sys/devices/virtual/gpio/gpio39/value", O_RDWR); //要操作的设备文件节点取自第 1 个参数
	while(1)
	{
		write(fd, "0", 2);
		usleep((delay_time_off+cnt%3)*1);
		write(fd, "1", 2);
		printf("cnt %d\n", ++cnt);
		usleep(delay_time_on*1000);
		if(delay_time_off1>0)
		{
			write(fd, "0", 2);
			usleep((delay_time_off1)*1);
		}
		if(delay_time_on1>0)
		{
			write(fd, "1", 2);
			printf("cnt1 %d\n", cnt);
			usleep(delay_time_on1*1000);
		}
	}
	return 0;
}

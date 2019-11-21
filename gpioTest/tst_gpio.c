#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <asm/ioctls.h>
#include <time.h>
#include <pthread.h>
#include "gpio.h"
static void show_help(void) // 打印本程序的用法
{
	        printf("example:\n");
		        printf(" gpio_test /dev/gpio-xxx H #set gpio output higth \n");
			        printf(" gpio_test /dev/gpio-xxx L #set gpio output low \n");
				        printf(" gpio_test /dev/gpio-xxx R #read gpio input status(H/L) \n");
}

int main(int argc, char *argv[])
{
	        int fd;
		        char cmd;
			        int data;
	int i = 0;
	fd = open("/dev/gpio-P1.7", O_RDWR); //要操作的设备文件节点取自第 1 个参数
	if (fd < 0) {
	printf("faile to open %s \n", "/dev/gpio-P1.7");
	return -1;
	}
	ioctl(fd, SET_GPIO_HIGHT);
	while(1)
	{
		ioctl(fd, SET_GPIO_HIGHT);
		ioctl(fd, SET_GPIO_HIGHT);
	}
							        return 0;
}

#include <stdio.h>
#include <linux/gpio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include "gpioconfig.h"

int main(int argc, char *argv[])
{
	int fd;
	int ret;
	char str[200] = {0};
	struct gpioline_info lineinfo = {0};
	struct gpioevent_request eventreq = {0};
	struct gpiochip_info chipinfo = {0};

	struct pollfd fdset[2];
	char buf[MAX_BUF];
	int len;
	int rc;

    eventreq.handleflags = GPIOHANDLE_REQUEST_INPUT;
	eventreq.lineoffset = 1;
	//strcpy(eventreq.consumer_label, "sysfs");
	eventreq.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
	printf("Hello, world\n");
	fd = open("/dev/gpiochip0", O_NONBLOCK);
	ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &chipinfo);
	printf("GPIO_GET_CHIPINFO_IOCTL is %s %s %d\n", chipinfo.name, chipinfo.label, chipinfo.lines);
	memset(str, 0, sizeof(str));
	if((ret=ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &lineinfo)) == 0)
	{
		printf("GPIO_GET_LINEINFO_IOCTL is name:%s consumer:%s flag:%x\n", lineinfo.name, lineinfo.consumer, lineinfo.flags);
	}
	else
	{
		printf("GPIO_GET_LINEINFO_IOCTL error %d\n", ret);
	}
	

	if((ret=ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &eventreq)) >= 0)
	{
		printf("GPIO_GET_LINEEVENT_IOCTL is fd:%d\n", eventreq.fd);

		while (1) {
			memset((void*)fdset, 0, sizeof(fdset));

			fdset[0].fd = STDIN_FILENO;
			fdset[0].events = POLLIN;

			fdset[1].fd = eventreq.fd;
			fdset[1].events = POLLIN;

			rc = poll(fdset, 2, 1000);

			if (rc < 0) {
				printf("\npoll() failed!\n");
				return -1;
			}

			if (rc == 0) {
				printf(".");
			}
			if (fdset[1].revents & POLLIN) {
				lseek(fdset[1].fd, 0, SEEK_SET);  // Read from the start of the file
				len = read(fdset[1].fd, buf, MAX_BUF);
				printf("gpio interrupt! \n");
			}

			if (fdset[0].revents & POLLIN) {
				(void)read(fdset[0].fd, buf, 1);
				printf("\npoll() stdin read 0x%2.2X\n", (unsigned int) buf[0]);
			}

			fflush(stdout);
		}
		close(eventreq.fd);
		close(fd);
	}
	else
	{
		printf("GPIO_GET_LINEEVENT_IOCTL error %d\n", ret);
		perror("error is ");
		close(fd);
	}
	return 0;
}

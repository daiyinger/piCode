#define _GNU_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <sys/select.h>

#include <string.h>

#include "rt_vbus_user.h"

#define handle_error(msg, err) \
    do { perror(msg); exit(err); } while (0)

#define BUFLEN 1024
char buf[BUFLEN];

int main(int argc, char *argv[])
{
	const char *recv_path_const = "/home/root/";
    struct rt_vbus_request req;
    req.name      = "vecho";
    req.prio      = 20;
    req.is_server = 1;
    req.oflag     = O_RDWR;
    req.recv_wm.low  = 500;
    req.recv_wm.high = 1000;
    req.post_wm.low  = 500;
    req.post_wm.high = 1000;

	if(access(recv_path_const, 0) == 0)
	{
		chdir(recv_path_const);
	}

    /*int rwfd = ioctl(ctlfd, VBUS_IOCREQ, &req);
    if (rwfd < 0)
        handle_error("ioctl error", rwfd);
    close(ctlfd);*/

    while(1)
    {
		int ctlfd = open("/dev/rtvbus", O_RDWR);
		if (ctlfd < 0)
		{
			handle_error("open error", ctlfd);
			break;
		}
		int rwfd = ioctl(ctlfd, VBUS_IOCREQ, &req);
		//printf("closed file\n");
		close(ctlfd);
		if (rwfd < 0)
		{
			handle_error("ioctl error", rwfd);
		}

		FILE *fp;  
		int len = read(rwfd, buf, 4);	//read file name length
		if(len > 0)
		{
			len = *((int *)buf);
			//printf("file name len:%d\n", len);
			len =  read(rwfd, buf, len);
			buf[len] = '\0';
			char *p = strrchr(buf, '/');
			p += 1; //point after last /
			printf("received file :%s\n", p);
			if((fp=fopen(p,"wb"))==NULL)  
			{
				printf("open write file error\n");
				close(rwfd);
				break;
			}
		}
		else
		{
			close(rwfd);
			break;
		}
		while(1)
		{
			/* 从设备端口/dev/rtvbus读取文件内容 */
			int len = read(rwfd, buf, sizeof(buf)-1);
			if(len > 0)
			{
				//printf("recv message: %d\n", len);
				fwrite(buf, 1, len, fp);
			}	
			else if(len < 0)
			{
				printf("read error %d\n", len);
				break;
			}
			else
			{
				//printf("read len 0\n");
				break;
			}
		}
		fclose(fp);
		close(rwfd);
	}
	exit(0);
}

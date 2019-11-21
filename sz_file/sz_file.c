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
    FILE *fp;
    char *fname;
    int i = 0;
    int ctlfd = open("/dev/rtvbus", O_RDWR);
    if (ctlfd < 0)
        handle_error("open error", ctlfd);

    struct rt_vbus_request req;
    req.name      = "android";
    req.prio      = 20;
    req.is_server = 0;
    req.oflag     = O_RDWR;
    req.recv_wm.low  = 500;
    req.recv_wm.high = 1000;
    req.post_wm.low  = 500;
    req.post_wm.high = 1000;

    int rwfd = ioctl(ctlfd, VBUS_IOCREQ, &req);
    if (rwfd < 0)
        handle_error("ioctl error", rwfd);
    close(ctlfd);

	/* 向设备端口/dev/rtvbus写字符串 */
    /*for (int i = 1; i < argc; i++) {
        write(rwfd, argv[i], strlen(argv[i]));
        write(rwfd, " ", 1);
        printf("%s ", argv[i]);
    }*/
    fname = argv[1];
    printf("send file: %s to os2\n", fname);
    int file_name_len = strlen(fname);

    //printf("file name len is %d, %x\n", file_name_len, file_name_len);
    write(rwfd, &file_name_len, 4);
    write(rwfd, fname, strlen(fname));
    if((fp=fopen(fname,"rb"))==NULL) 
    {
	return -1;
    }
while(!feof(fp))
{
buf[i%(BUFLEN-1)]=fgetc(fp);
	
i++;
if(i%(BUFLEN-1) == 0)
{
	 write(rwfd, buf, (BUFLEN-1));
}
}
    write(rwfd, buf, i%(BUFLEN-1)-1);
    printf("\n");

	fclose(fp);
    close(rwfd);
    exit(0);
}

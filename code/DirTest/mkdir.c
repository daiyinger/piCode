#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv)
{
	int ret = -1;
	ret = mkdir("test",0777);
	if( -1 == ret )
	{
		perror("mkdir");
		return -1;
	}
}


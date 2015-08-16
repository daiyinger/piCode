#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 512
int main(int argc,char **argv)
{
	char *buf = NULL;
	//分配内存，用来存放工作目录的文件名
	buf = malloc(MAX);
	if( NULL == buf )
	{
		perror("malloc");
		return -1;
	}
	memset(buf,'\0',MAX);
	//获取当前工作目录，放在buf里面，大小不超过MAX
	if(NULL == getcwd(buf,MAX) )
	{
		perror("getcwd");
		return -1;
	}
	printf("cur dir is %s\n",buf);
	//通过参数，来改变当前的工作目录
	if(-1 == chdir(argv[1]))
	{
		perror("chdir");
	}
	memset(buf,'\0',MAX);
	//获取当前的工作目录
	if(NULL == getcwd(buf,MAX))
	{
		perror("getcwd");
		return -1;
	}
	printf("cur dir is %s\n",buf);
	free(buf);	//释放申请的内存
	return 0;
}

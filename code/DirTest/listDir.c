#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

//打开一个目录，读取目录里面的每一个文件的信息
int main(int argc,char **argv)
{
	DIR * dir = NULL;
	struct dirent *ent;

	//根据命令行输入的参数，打开一个目录，返回目录流（后面所有操作的依据）
	dir = opendir(argv[1]);
	if(NULL == dir )
	{
		perror("opendir");
		return -1;
	}
	//读目录
	//一次只能读取一个目录项，所以需要循环；也需要判断循环的结束（目录尾）
	errno = 0;
	while(1)
	{
		ent = readdir(dir);
		if( NULL == ent)
		{
			if( 0 == errno )
			{
				//代表到达目录尾部
				printf("end of dir\n");
				break;
			}else
			{
				//读出错了
				perror("readdir");
				return -1;
			}
		}
		//显示目录包含信息
		printf("目录包含：%s\n",ent->d_name);
	}
	closedir(dir);
	return 0;
}


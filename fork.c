#define _CRT_SECURE_NO_WARNINGS 1

int main(void)
{
	pid_t pid;
	printf("Before: pid is %d\n", getpid());
	if ((pid = fork()) == -1)perror("fork()"), exit(1);
	printf("After:pid is %d, fork return %d\n", getpid(), pid);
	sleep(1);
	return 0;
}


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int ret = fork();
	if (ret < 0) {
		perror("fork");
		return 1;
	}
	else if (ret == 0) { //child
		printf("I am child : %d!, ret: %d\n", getpid(), ret);
	}
	else { //father
		printf("I am father : %d!, ret: %d\n", getpid(), ret);
	}
	sleep(1);
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_val = 0;

int main()
{
	pid_t id = fork();
	if (id < 0) {
		perror("fork");
		return 0;
	}
	else if (id == 0) { //child,子进程肯定先跑完，也就是子进程先修改，完成之后，父进程再读取
		g_val = 100;
		printf("child[%d]: %d : %p\n", getpid(), g_val, &g_val);
	}
	else { //parent
		sleep(3);
		printf("parent[%d]: %d : %p\n", getpid(), g_val, &g_val);
	}
	return 0;
}


////与环境相关，观察现象即可
//child[3046]: 100 : 0x80497e8
//parent[3045] : 0 : 0x80497e8
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include"ioctl.h"

int a,b;

void add(int a,int b)
{
 printf("addition is %d\n",a+b);
}

void signal_handler(int signum)
{
	printf("Entered signal handler\n");
	if(signum==SIGUSR2)
	{
		add(a,b);
	}
}

int main()
{
	int fd;
	int args;
	signal(SIGUSR2,signal_handler);
	
	fd = open("/dev/user",O_RDWR);
	if(fd<0)
	{
		printf("error\n");
		return -1;
	}
	
	printf("Enter two numbers\n");
	scanf("%d%d",&a,&b);
	printf("Enter 1 for addition\n");
	scanf("%d",&args);
	if(args==1)
	ioctl(fd,IOCTL_SEND_SIG,args);
	else{
	ioctl(fd,IOCTL_CMD);
	printf("Enter correct number\n");}
	printf("Ioctl executed\n");

	close(fd);
	return 0;
}

#include <unistd.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <stdio.h> 
#include <stdlib.h>

#ifndef NOFILE 
#define NOFILE 3 
#endif

void init_daemon() 
{ 
int pid; 
int i; 
if(pid = fork()) exit(0); //父进程，退出 

else if(pid < 0) exit(1); //fork失败 

/* 子进程继续执行 */ 
setsid(); //创建新的会话组，子进程成为组长，并与控制终端分离 

/* 防止子进程（组长）获取控制终端 */ 
if(pid = fork()) exit(0); //父进程，退出 

else if(pid < 0) exit(1); //fork错误，退出 

/* 第二子进程继续执行 , 第二子进程不再是会会话组组长*/ 

for(i = 0; i < NOFILE; i++) /* 关闭打开的文件描述符*/ 
{ 
close(i); 
} 
chdir("/tmp"); /* 切换工作目录 */ 
umask(0); /* 重设文件创建掩码 */ 
return; 
} 

int main() 
{ 
FILE *fp; 

signal(SIGCHLD, SIG_IGN); /* 忽略子进程结束信号，防止出现僵尸进程 */ 

init_daemon(); 

while(1) 
{ 
sleep(1);
if((fp = fopen("test.log", "a")) != NULL) 
{ 
fprintf(fp, "%s\n", "test message"); 
fclose(fp); 
} 
} 
return 0; 
}
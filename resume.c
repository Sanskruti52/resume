#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
void handle_signal(int sig)
{
	if (sig==SIGUSR1)
	{
		printf("Parent:Child process is resumed..\n");
	}
}
int main()
{
	pid_t pid;
	signal(SIGUSR1,handle_signal);
	signal(SIGUSR2,handle_signal);
	pid=fork();
	if(pid==0)
	{
		while(1)
		{
			printf("Child Running...\n");
			sleep(1);
		}
		pause();
	}
	else
	{
		sleep(3);
		kill(pid,SIGSTOP);
		raise(SIGUSR1);
		sleep(5);
		kill(pid,SIGCONT);
		raise(SIGUSR2);
		sleep(5);
		kill(pid,SIGTERM);
		wait(NULL);
		printf("Parent:Child process  terminated...");
	}
	return 0;
}
	

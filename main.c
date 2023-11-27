#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>


void read_n_write(int fd_src, int fd_dst)
{
		int filefd = open("output.txt", O_WRONLY | O_CREAT, 0666);
        if (filefd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            write(filefd, buffer, bytes_read);
        }

        close(filefd);
        close(pipefd[0]);
}

//function to split the input and load it correctly in the struct
//		if we get a cmd like "ls -l -a" we need to store it in a char** like ["ls","-l","-a", NULL]
int main(int argc, char **argv)
{
	//t_input args;
	int pipefd[2];
	char *args[] = {"/bin/ls", "-al", NULL};

	if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
	pid_t pid1 = fork();
    if (pid1 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(args[0], args, NULL);
	}

	pid_t pid2 = fork();
    if (pid2 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	char *args2[] = {"/usr/bin/grep", "main", NULL};
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execve(args2[0], args2, NULL);
	}
	return (0);
}

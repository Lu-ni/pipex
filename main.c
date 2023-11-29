#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	//t_input args;
	//./pipex ola "/bin/ls -al" "/usr/bin/grep lib" ola
	int pipefd[2];
	t_input input;

	parser(argc, argv, &input);

	dup2(open(input.infile, O_RDONLY), STDIN_FILENO);
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
		execve(input.cmd1[0], input.cmd1, NULL);
	}

	pid_t pid2 = fork();
	int pipefd2[2];
	if (pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pid2 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	if (pid2 == 0)
	{
		dup2(open(input.outfile, O_CREAT|O_WRONLY|O_TRUNC), STDOUT_FILENO);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execve(input.cmd2[0], input.cmd2, NULL);
	}
	return (0);
}

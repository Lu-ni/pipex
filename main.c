#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "libft/libft.h"
#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void close_pipe(int pipefd[10][2], int i_last)
{
	int i;
	i=0;
	while (i<i_last)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

int main(int argc, char **argv, char *envp[])
{
	int pipefd[10][2];
	t_input input;
	int i_cmd;
	pid_t pid;
	char **cmd;

	i_cmd = 0;
	int i_first = 0;
	int i_last = argc - 4;
	input.path = get_path(envp);
	if(parser(argc, argv, &input))
		exit(EXIT_FAILURE);

	while ( i_cmd < i_last)
	{
		if (pipe(pipefd[i_cmd]) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i_cmd++;
	}
	i_cmd = 0;
	while(i_cmd <= i_last)
	{
		cmd = get_cmd(argv[i_cmd + 2],input.path);
		if (!cmd)
		{
			perror("command not found");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (i_cmd == i_first)
			{
				int fd = open(input.infile, O_RDONLY);
				if (fd < 0)
				{
					error("no such file or directory: ", input.infile);
					exit(EXIT_FAILURE);
				}

				dup2(fd, STDIN_FILENO);
				dup2(pipefd[i_cmd][1], STDOUT_FILENO);
				close_pipe(&pipefd[0], i_last);
			}
			else if (i_cmd == i_last)
			{
				dup2(open(input.outfile, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR), STDOUT_FILENO);
				dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
				close_pipe(&pipefd[0], i_last);
			}
			else
			{
				dup2(pipefd[i_cmd][1], STDOUT_FILENO);
				dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
				close_pipe(&pipefd[0], i_last);
			}
			execve(cmd[0], cmd, envp);
		}
		int i = 0;
		while(cmd[i])
			free(cmd[i++]);
		free(cmd);
		i_cmd ++;
	}
	int i = 0;
	i = 0;
	while(input.path[i])
		free(input.path[i++]);
	free(input.path);
	close_pipe(&pipefd[0], i_last);
	return (0);
}

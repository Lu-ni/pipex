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

void close_pipe(int pipefd[10][2], t_input *input)
{
	int i;
	i=0;
	while (i < input->i_last)
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

	i_cmd = 0;
	int i_first = 0;
	input.i_last = argc - 4;
	input.path = get_path(envp);
	if(parser(argc, argv, &input))
		exit(EXIT_FAILURE);

	while (i_cmd < input.i_last)
	{
		if (pipe(pipefd[i_cmd]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i_cmd++;
	}
	i_cmd = 0;
	while(i_cmd <= input.i_last)
	{
		input.cmd = get_cmd(argv[i_cmd + 2],input.path);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (i_cmd == i_first)
				cmd_first(&input, pipefd, i_cmd);
			else if (i_cmd == input.i_last)
				cmd_last(&input, pipefd, i_cmd);
			else
				cmd_mid(&input, pipefd, i_cmd);
			execve(input.cmd[0], input.cmd, envp);
		}
		if(input.cmd)
			free_cmd(input.cmd);
		i_cmd ++;
	}
	// freeing and closing pipes
	int i = 0;
	i = 0;
	while(input.path[i])
		free(input.path[i++]);
	free(input.path);
	close_pipe(&pipefd[0], &input);
	return (0);
}

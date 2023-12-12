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

void init(int argc, char **argv, t_input *input, int pipefd[10][2])
{
	if(parser(argc, argv, input))
		exit(EXIT_FAILURE);
	while (input->i_cmd < input->i_last)
	{
		if (pipe(pipefd[input->i_cmd]) == -1)
		{
			error("pipe", NULL);
			exit(EXIT_FAILURE);
		}
		input->i_cmd++;
	}
	input->i_cmd = 0;
}

int open_pid()
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		error("fork", NULL);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int main(int argc, char **argv, char *envp[])
{
	int pipefd[10][2];
	t_input input = {.i_cmd = 0, .i_last = argc - 4, .path = get_path(envp)};
	pid_t pid;
	int i;

	init(argc, argv, &input, pipefd);
	while(input.i_cmd <= input.i_last)
	{
		input.cmd = get_cmd(argv[input.i_cmd + 2],input.path);
		pid = open_pid();
		if (pid == 0)
			run_cmd(&input, pipefd,envp);
		if(input.cmd)
			free_cmd(input.cmd);
		input.i_cmd ++;
	}
	i = 0;
	while(input.path[i])
		free(input.path[i++]);
	free(input.path);
	close_pipe(&pipefd[0], &input);
	return (0);
}

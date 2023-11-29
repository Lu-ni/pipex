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

int main(int argc, char **argv)
{
	int pipefd[10][2];
	t_input input;
	int i_cmd;
	pid_t pid;
	char **cmd;

	i_cmd = 0;
	int i_first = 0;
	int i_last = argc - 4;

	parser(argc, argv, &input);

	while(i_cmd <= i_last)
	{
		if ( i_cmd != i_last)
		{
			if (pipe(pipefd[i_cmd]) == -1) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		cmd = ft_split(argv[i_cmd + 2], ' ');
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
				dup2(open(input.infile, O_RDONLY), STDIN_FILENO);
				close(pipefd[i_cmd][0]);
				dup2(pipefd[i_cmd][1], STDOUT_FILENO);
				close(pipefd[i_cmd][1]);
				execve(cmd[0], cmd, NULL);
			}
			if (i_cmd == i_last)
			{
				dup2(open(input.outfile, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR), STDOUT_FILENO);
				close(pipefd[i_cmd - 1][1]);
				dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
				//close(pipefd[i_cmd - 1][0]);
				execve(cmd[0], cmd, NULL);
			}
			dup2(pipefd[i_cmd][1], STDOUT_FILENO);
			//close(pipefd[i_cmd][0]);
			//close(pipefd[i_cmd][1]);
			close(pipefd[i_cmd - 1][1]);
			dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
			//close(pipefd[i_cmd - 1][0]);
			execve(cmd[0], cmd, NULL);
		}
		i_cmd ++;
	}
	return (0);
}

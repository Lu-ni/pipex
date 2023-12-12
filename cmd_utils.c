#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"


void free_cmd(char **cmd)
{
	int i;

	i = 0;
	while(cmd[i])
		free(cmd[i++]);
	free(cmd);
}

char **get_cmd(char *raw, char **path)
{
	char **cmd;
	char *tmp;
	cmd = ft_split(raw, ' ');
	while(*path)
	{
		tmp = ft_strjoin(*path,cmd[0]);
		if (!access(tmp, X_OK))
		{
			free(cmd[0]);
			cmd[0] = tmp;
			return(cmd);
			
		}
		free(tmp);
		path++;
	}
	//free everything from the split()
	free_cmd(cmd);	
	return NULL;
}

void cmd_first(t_input *input, int pipefd[10][2],int i_cmd, int i_last)
{
	int fd = open(input->infile, O_RDONLY);
	if (fd < 0)
	{
		error("no such file or directory: ", input->infile);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[i_cmd][1], STDOUT_FILENO);
	}
	close_pipe(&pipefd[0], i_last);
}

void cmd_mid(int pipefd[10][2],int i_cmd, int i_last)
{
	dup2(pipefd[i_cmd][1], STDOUT_FILENO);
	dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
	close_pipe(&pipefd[0], i_last);
}

void cmd_last(t_input *input, int pipefd[10][2],int i_cmd, int i_last)
{
	dup2(open(input->outfile, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR), STDOUT_FILENO);
	dup2(pipefd[i_cmd - 1][0], STDIN_FILENO);
	close_pipe(&pipefd[0], i_last);
}

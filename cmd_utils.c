/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:58:44 by lnicolli          #+#    #+#             */
/*   Updated: 2023/12/19 15:40:47 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

char	**get_cmd(char *raw, char **path)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(raw, ' ');
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd[0]);
		if (!access(tmp, X_OK))
		{
			free(cmd[0]);
			cmd[0] = tmp;
			return (cmd);
		}
		free(tmp);
		path++;
	}
	free_cmd(cmd);
	return (NULL);
}

void	cmd_first(t_input *input, int pipefd[10][2])
{
	int	fd;

	if (access(input->infile, R_OK) | !input->cmd)
	{
		if (access(input->infile, R_OK))
			error("no such file or directory: ", input->infile);
		if (!input->cmd)
			error("command not found", NULL);
		close_pipe(&pipefd[0], input);
		exit(EXIT_FAILURE);
	}
	fd = open(input->infile, O_RDONLY);
	if (fd < 0)
	{
		error("no such file or directory: ", input->infile);
		close_pipe(&pipefd[0], input);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		dup2(pipefd[input->i_cmd][1], STDOUT_FILENO);
	}
	close_pipe(&pipefd[0], input);
}

void	cmd_last(t_input *input, int pipefd[10][2])
{
	if (!input->cmd)
	{
		error("command not found", NULL);
		close_pipe(&pipefd[0], input);
		open(input->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		exit(EXIT_FAILURE);
	}
	dup2(open(input->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
			| S_IWUSR), STDOUT_FILENO);
	dup2(pipefd[input->i_cmd - 1][0], STDIN_FILENO);
	close_pipe(&pipefd[0], input);
}

void	run_cmd(t_input *input, int pipefd[10][2], char *envp[])
{
	if (input->i_cmd == 0)
		cmd_first(input, pipefd);
	else if (input->i_cmd == input->i_last)
		cmd_last(input, pipefd);
	else
	{
		if (!input->cmd)
		{
			error("command not found", NULL);
			close_pipe(&pipefd[0], input);
			exit(EXIT_FAILURE);
		}
		dup2(pipefd[input->i_cmd][1], STDOUT_FILENO);
		dup2(pipefd[input->i_cmd - 1][0], STDIN_FILENO);
		close_pipe(&pipefd[0], input);
	}
	execve(input->cmd[0], input->cmd, envp);
}

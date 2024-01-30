/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:03:35 by lnicolli          #+#    #+#             */
/*   Updated: 2023/12/19 15:48:28 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	close_pipe(int pipefd[10][2], t_input *input)
{
	int	i;

	i = 0;
	while (i < input->i_last)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

void	init(int argc, char **argv, t_input *input, int pipefd[10][2])
{
	if (parser(argc, argv, input))
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

int	open_pid(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		error("fork", NULL);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	free_path(t_input *input)
{
	int		i;

	i = 0;
	while (input->path[i])
		free(input->path[i++]);
	free(input->path);
}

int	main(int argc, char **argv, char *envp[])
{
	int		pipefd[10][2];
	t_input	input;
	pid_t	pid;

	if (argc < 4)
		return (0);
	input.i_cmd = 0;
	input.i_last = argc - 4;
	input.path = get_path(envp);
	init(argc, argv, &input, pipefd);
	while (input.i_cmd <= input.i_last)
	{
		input.cmd = get_cmd(argv[input.i_cmd + 2], input.path);
		pid = open_pid();
		if (pid == 0)
			run_cmd(&input, pipefd, envp);
		if (input.cmd)
			free_cmd(input.cmd);
		input.i_cmd++;
	}
	close_pipe(&pipefd[0], &input);
	free_path(&input);
	return (0);
}

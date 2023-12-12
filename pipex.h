/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:06:09 by lnicolli          #+#    #+#             */
/*   Updated: 2023/12/12 18:06:16 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_input
{
	char	*infile;
	char	*outfile;
	char	**path;
	char	*last_cmd;
	int		i_last;
	int		i_cmd;
	char	**cmd;
}			t_input;

int			parser(int argc, char **argv, t_input *args);
char		**get_path(char *env[]);
char		**get_cmd(char *raw, char **path);
void		error(char *msg, char *subject);
void		free_cmd(char **cmd);
void		close_pipe(int pipefd[10][2], t_input *input);
void		cmd_first(t_input *input, int pipefd[10][2]);
void		run_cmd(t_input *input, int pipefd[10][2], char *envp[]);
void		cmd_last(t_input *input, int pipefd[10][2]);
#endif

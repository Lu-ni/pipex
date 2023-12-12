#include "libft/libft.h"
#include "pipex.h"
#include <stdlib.h>

int	parser(int argc, char **argv, t_input *args)
{
	if (argc < 5)
		return (1);
	args->infile = argv[1];
	args->outfile = argv[argc - 1];
	return (0);
}

char	**get_path(char *env[])
{
	char	**tmps;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	tmps = ft_split(&env[i][5], ':');
	i = 0;
	while (tmps[i])
	{
		tmp = tmps[i];
		tmps[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (tmps);
}

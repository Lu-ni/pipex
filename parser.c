#include "libft/libft.h"
#include "pipex.h"

int parser(int argc,char **argv, t_input *args)
{
	if (argc < 5)
		return 1;
	args->infile = ft_strdup(argv[1]);
	args->outfile = ft_strdup(argv[argc - 1]);
	return (0);
}

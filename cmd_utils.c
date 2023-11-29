#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char **get_cmd(char *raw, char **path)
{
	char **cmd;
	char *tmp;
	cmd = ft_split(raw, ' ');
	while(*path)
	{
		tmp = ft_strjoin(*path,cmd[0]);
		printf("testing %s\n",tmp);
		if (!access(tmp, X_OK))
		{
			printf("ex find for %s\n",tmp);
			free(cmd[0]);
			cmd[0] = tmp;
			return(cmd);
			
		}
		free(tmp);
		path++;
	}
	return NULL;
}

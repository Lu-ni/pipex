#ifndef PIPEX_H
# define PIPEX_H
typedef struct s_input
{
	char *infile;
	char *outfile;
	char **path;
} t_input;
int parser(int argc,char **argv, t_input *args);
char **get_path(char *env[]);
char **get_cmd(char *raw, char **path);
void error(char *msg, char *subject);
#endif

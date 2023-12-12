#ifndef PIPEX_H
# define PIPEX_H
typedef struct s_input
{
	char *infile;
	char *outfile;
	char **path;
	char *last_cmd;
} t_input;
int parser(int argc,char **argv, t_input *args);
char **get_path(char *env[]);
char **get_cmd(char *raw, char **path);
void error(char *msg, char *subject);
void free_cmd(char **cmd);
void close_pipe(int pipefd[10][2], int i_last);
void cmd_first(t_input *input, int pipefd[10][2],int i_cmd, int i_last);
void cmd_mid(int pipefd[10][2],int i_cmd, int i_last);
void cmd_last(t_input *input, int pipefd[10][2],int i_cmd, int i_last);
#endif

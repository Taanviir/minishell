/* commit
- split up parser and made new file constructor.c moved all constructors there
- added print functions to test.c
- added nulterminate function
 */
#include "minishell.h"

void print(t_cmd *root);

void print_exec(t_cmd *c)
{
	t_exec *cmd;

	cmd = (t_exec *)c;
	printf("   Node_%p [label=\"%s\"]\n", (void *)cmd, cmd->argv[0]);
	for (int i = 1; cmd->argv[i]; i++)
	{
		printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->argv[i]);
        printf("   Node_%p [label=\"%s\"]\n", (void *)cmd->argv[i], cmd->argv[i]);
	}
}

void print_redir(t_cmd *c)
{
	t_redircmd *redir;

	redir = (t_redircmd *)c;
	print(redir->cmd);
	printf("redirected %d to file:%s\n", redir->fd, redir->fp);
}

void print_pipe(t_cmd *c)
{
	t_pipecmd *cmd;

	cmd = (t_pipecmd *)c;
	printf("   Node_%p [label=\"|\"]\n", (void *)cmd);
    printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->left);
    printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->right);
	print(cmd->left);
	print(cmd->right);
}

void print_seq(t_cmd *c)
{
	t_seqcmd *cmd;

	cmd = (t_seqcmd *)c;
	print(cmd->left);
	printf("sequenced\n");
	print(cmd->right);
}

void print_bgcmd(t_cmd *c)
{
	t_bgcmd *cmd;

	cmd = (t_bgcmd *)c;
	print(cmd->cmd);
}

typedef void (*printers)(t_cmd *c);

printers prints[5] = {
	print_exec,
	print_redir,
	print_pipe,
	print_seq,
	print_bgcmd,
};

void print(t_cmd *root)
{
	prints[root->type](root);
}

int main(void)
{
	char *cmd = ft_memcpy(malloc(38), "ping -c 5 google.com | grep rtt | cat", 38);
	printf("digraph Trie {\n");
	t_cmd *root = parsecmd(cmd);
	print(root);
	printf("}\n");
}

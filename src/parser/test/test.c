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
	printf("   Node_%p [label=\"%s\" shape=box style=filled color=darkslategray4]\n", (void *)cmd, cmd->argv[0]);
	printf("   Node_%p -> Node_%p1\n", (void *)cmd, (void *)cmd);
	printf("   Node_%p1 [shape=box color=darkslategray4 label=\"\n", (void *)cmd);
	for (int i = 1; cmd->argv[i]; i++)
	{
		if (ft_strchr(cmd->argv[i], '"'))
		{
			for (int j = 0; cmd->argv[i][j]; j++) {
				if (cmd->argv[i][j] == '\"') printf("\\");
				printf("%c",cmd->argv[i][j]);
			}
		}
		else
			printf("%s\n", cmd->argv[i]);
	}
  	printf("\"]\n");
}

void print_redir(t_cmd *c)
{
	t_redircmd *redir;

	redir = (t_redircmd *)c;
	printf("   Node_%p [label=\"std: %d to %s\"]\n", (void *)redir, redir->fd, redir->fp);
    printf("   Node_%p -> Node_%p\n", (void *)redir, (void *)redir->cmd);
	print(redir->cmd);
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
	printf("   Node_%p [label=\";\"]\n", (void *)cmd);
    printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->left);
    printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->right);
	print(cmd->left);
	print(cmd->right);
}

void print_bgcmd(t_cmd *c)
{
	t_bgcmd *cmd;

	cmd = (t_bgcmd *)c;
	printf("   Node_%p [label=\"&\"]\n", (void *)cmd);
    printf("   Node_%p -> Node_%p\n", (void *)cmd, (void *)cmd->cmd);
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

int main(int argc, char **argv, char **envp)
{
	char *cmd;

	if (argc != 2) return 0;
	int i = atoi(argv[1]);

	int fd = open("test/inputs.txt", O_RDONLY);
	if (i == 0)
		cmd = get_next_line(fd);
	else {
		int j = -1;
		while (++j < i)
		{
			cmd = get_next_line(fd);
			if (!cmd)
			{
				close(fd);
				return 1;
			}
		}
	}
	close(fd);

	// char *cmd = readline("ghost>>");
	printf("digraph Trie {\n");
	t_cmd *root = parsecmd(cmd, envp);
	print(root);
	printf("}\n");
	free(cmd);
}

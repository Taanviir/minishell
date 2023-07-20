#include "test.h"

void	test(t_cmd *root)
{
	int saved_stdout = dup(STDOUT_FILENO);
	int fd = open("./test/test.dot", O_WRONLY | O_TRUNC);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("digraph Tree {\n");
	print(root);
	printf("}\n");
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	system("dot -Tpng test/test.dot > test/test.png");
}

#ifdef TEST_AUTOMATIC
int main(int argc, char **argv __attribute__((unused)), char **envp)
{
	char *cmd;

	if (argc != 2) return 0;
	int i = ft_atoi(argv[1]);

	int fd = open("inputs.txt", O_RDONLY);
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
	t_cmd *root = parsecmd(cmd, envp);
	test(root);
	free(cmd);
}
#endif

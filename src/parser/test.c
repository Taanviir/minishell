#include "minishell.h"

int main(void)
{
	char *cmd = "echo hello world 1 2 3 4 5 6 8 93 10 20 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2  222 2 2 2 2 2 2  2 2 2 2 2  22  2  2  | grep \"world\"";
	parsecmd(cmd);
}

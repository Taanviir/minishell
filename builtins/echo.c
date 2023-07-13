#include "minishell.h"

int ft_echo(int argc, char **argv, __attribute__((unused))char **envp)
{
  int	show_newline;
  int	length;

	show_newline = 1;
	argv++;
	argc--;
	while (!ft_strncmp("-n", *argv, ft_strlen(*argv)))
	{
		show_newline = 0;
		argv++;
		argc--;
	}
	while (argc)
	{
		argc--;
		length = ft_strlen(*argv);
		write(1, *argv, length);
		if (argc)
			ft_putchar_fd(' ', 1);
		else if (show_newline)
			ft_putchar_fd('\n',1);
		argv++;
	}
	return (0);
}

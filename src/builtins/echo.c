#include "minishell.h"

#define PROGRAM_NAME "echo"
#define AUTHORS "Samih"


int main(int argc, char **argv, char **envp)
{
  int	show_newline;
  int	length;

	show_newline = 1;
	while (**argv == '-')
	{
	if (*(*argv + 1) == 'n');
		show_newline = 0;
	(*argv)++;
	argc--;
	}
	while (argc)
	{
		length = ft_strlen(*argv) - 1;
		write(1, *argv, length);
		if (*(*argv + length) == '\n' && show_newline)
			ft_putchar('\n');
		argc--;
		(*argv)++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 19:21:58 by tanas             #+#    #+#             */
/*   Updated: 2023/07/30 19:21:58 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

void	ft_echo(char **argv)
{
	bool	show_newline;
	int		i;

	show_newline = true;
	i = 1;
	while (argv[i] && !ft_strncmp("-n", argv[i], 2))
	{
		show_newline = false;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
}

int	ft_exit(int err_num)
{
	g_signal.exit_status = err_num;
	printf("exit\n");
	exit(g_signal.exit_status);
}

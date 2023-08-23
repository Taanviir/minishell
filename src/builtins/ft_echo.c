/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:19:24 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 01:19:24 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_tilde(char *arg, t_env *env_list)
{
	if (!ft_strncmp("~+", arg, get_len("~+", arg)))
		return (ft_putstr_fd(get_env(env_list, "PWD"), 1), 1);
	else if (!ft_strncmp("~", arg, get_len("~", arg)))
		return (ft_putstr_fd(get_env(env_list, "HOME"), 1), 1);
	return (0);
}

int		ft_echo(int argc, char **argv, t_env *env_list)
{
	bool	show_newline;
	int		i;
	int		j;

	show_newline = true;
	i = 1;
	while (i < argc && !ft_strncmp("-n", argv[i], 2))
	{
		j = 1;
		while (argv[i][j] && argv[i][j] == 'n')
			j++;
		if (argv[i][j] && argv[i][j] != 'n')
		{
			show_newline = true;
			break ;
		}
		else if (!argv[i][j])
		{
			i++;
			show_newline = false;
			continue ;
		}
		i++;
	}
	while (i < argc)
	{
		if (!handle_tilde(argv[i], env_list))
			ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

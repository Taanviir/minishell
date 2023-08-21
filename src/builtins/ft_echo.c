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

int	ft_echo(t_exec *cmd, t_env *env_list)
{
	bool	show_newline;
	size_t	i;
	char	**tmp;

	show_newline = true;
	i = 1;
	tmp = cmd->argv;
	while (tmp[i] && !ft_strncmp("-n", tmp[i], get_len("-n", tmp[i])))
	{
		show_newline = false;
		i++;
	}
	while (i < cmd->argc)
	{
		if (!handle_tilde(tmp[i], env_list))
			ft_putstr_fd(tmp[i], 1);
		if (tmp[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

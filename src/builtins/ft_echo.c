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
	if (!ft_strncmp("~", arg, ft_strlen(arg)))
	{
		if (!ft_strncmp("~+", arg, get_len("~+", arg)))
			ft_putstr_fd(get_env(env_list, "PWD"), 1);
		else
			ft_putstr_fd(get_env(env_list, "HOME"), 1);
		return (1);
	}
	return (0);
}

int	ft_echo(t_exec *cmd, t_env *env_list)
{
	bool	show_newline;
	size_t	i;

	show_newline = true;
	i = 1;
	while (cmd->argv[i] && !ft_strncmp("-n", cmd->argv[i], get_len("-n", cmd->argv[i])))
	{
		show_newline = false;
		i++;
	}
	while (i < cmd->argc)
	{
		if (!handle_tilde(cmd->argv[i], env_list))
			ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

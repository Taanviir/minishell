/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:20:16 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 01:20:16 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_check(t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	while (exec->argv && exec->argv[++i])
	{
		j = -1;
		while (exec->argv[i][++j] && (!ft_is_digit(exec->argv[i][j]) || j > 19))
		{
			printf("minishell: exit: %s: numeric argument required\n", exec->argv[i]);
			return (255);
		}
	}
	if (exec->argc == 2 && ft_strncmp(exec->argv[1], "255", 3) > 0)
		return (ft_atoi(exec->argv[1]) % 256); //! ft_atoi can break
	else if (exec->argc == 2)
		return (ft_atoi(exec->argv[1]));
	return (0);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	t_exec	*exec;

	if (cmd)
	{
		exec = (t_exec *) cmd;
		if (exec->argc > 2)
			return (printf("minishell: exit: too many arguments\n"), 1);
		g_exit_status = exit_check((t_exec *) cmd);
	}
	free_tree(cmd);
	free_list(*env_list);
	printf("exit\n");
	exit(g_exit_status);
}

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

// TODO handle exit status
// * deleted or moved or renamed dir throws err
// * permissions issue
int	ft_pwd(t_env *env_list)
{
	char	*path;

	path = get_env(env_list, "PWD");
	printf("%s\n", path);
	return (0);
}

int	ft_echo(char **argv)
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
	return (0);
}

int	ft_exit(t_cmd *cmd, t_env **env_list)
{
	t_exec	*exec;
	int	i;
	int	j;

	if (cmd)
	{
		exec = (t_exec *) cmd;
		i = 0;
		while (exec->argv && exec->argv[++i])
		{
			j = -1;
			while (exec->argv[i][++j] && !ft_is_digit(exec->argv[i][j]))
			{
				printf("minishell: exit: %s: numeric argument required\n", exec->argv[i]);
				g_exit_status = 255;
			}
		}
		if (exec->argc > 2)
			return (printf("minishell: exit: too many arguments\n"), 1);
		if (exec->argc == 2 && ft_strncmp(exec->argv[1], "255", 3) > 0)
			g_exit_status = (ft_atoi(exec->argv[1]) % 256);
		else if (exec->argc == 2)
			g_exit_status = ft_atoi(exec->argv[1]);
	}
	free_tree(cmd);
	free_list(*env_list);
	printf("exit\n");
	exit(g_exit_status);
}

// TODO handle exit status
int	ft_env(char **argv, t_env **env_list)
{
	t_env	*temp;

	if (argv[1])
		return (printf("env: %s: No such file or directory\n", argv[1]), 1);
	temp = *env_list;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}

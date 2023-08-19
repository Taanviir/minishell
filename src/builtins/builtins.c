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

int	ft_pwd(t_env *env_list)
{
	char	*path;

	path = get_env(env_list, "PWD");
	printf("%s\n", path);
	return (0);
}

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

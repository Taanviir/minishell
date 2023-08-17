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
// * doesnt do anyhting with too many args (>1)
// * always returns 0
// * deleted or moved or renamed dir throws err
// * permissions issue
int	ft_pwd(t_env *env_list)
{
	char	*path;

	path = get_env(env_list, "PWD");
	printf("%s\n", path);
	return (0);
}

int	ft_echo(t_exec *cmd)
{
	bool		show_newline;
	size_t		i;

	show_newline = true;
	i = 1;
	while (cmd->argv[i] && !ft_strncmp("-n", cmd->argv[i], get_len("-n", cmd->argv[i])))
	{
		show_newline = false;
		i++;
	}
	while (i < cmd->argc)
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (show_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

// TODO handle exit status
// * too many args (>1) prints bash: exit: too many arguments; doesnt exit but $? is 1
// * non numeric args prints bash: exit: 1a: numeric argument required; exits with 255
// * no args exits with 0
// * exit code above 255 does {code} % 256 and exits with that value
int	ft_exit(char **argv, int err_num, t_env **env_list)
{
	// if (argv[1])
	(void) argv;
	free_list(*env_list);
	g_exit_status = err_num;
	printf("exit\n");
	// return (g_exit_status);
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

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

// TODO handle exit status
// * too many args (>1) prints bash: exit: too many arguments; doesnt exit but $? is 1
// * non numeric args prints bash: exit: 1a: numeric argument required; exits with 255
// * no args exits with 0
// * exit code above 255 does {code} % 256 and exits with that value
int	ft_exit(char **argv, int err_num, t_env **env)
{
	// if (argv[1])
	(void) argv;
	free_list(*env);
	g_exit_status = err_num;
	printf("exit\n");
	// return (g_exit_status);
	exit(g_exit_status);
}

// TODO handle exit status
// * should not handle arguments or options
int	ft_env(char **argv, t_env **env)
{
	t_env	*temp;

	if (argv[1])
		return (printf("env: %s: No such file or directory\n", argv[1]), 1);
	temp = *env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	// TODO handle empty vars
	// * env will display vars with empty string like WSLENV=
	// * env will not display vars with NULL however
	return (0);
}

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

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
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

int	ft_exit(int err_num, t_env **env)
{
	//free_env_list(env);
	(void) env;
	g_signal.exit_status = err_num;
	printf("exit\n");
	exit(g_signal.exit_status);
}

int	ft_env(char **argv, t_env **env)
{
	t_env	*temp;

	if (argv[1])
		return (printf("env: %s: No such file or directory\n", argv[1]), 1);
	temp = *env;
	while (temp)
	{
		printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
		if (temp == *env)
			break ;
	}
	return (0);
}

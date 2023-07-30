/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/31 01:20:07 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int ft_export(char **argv, char **envp)
{
	int	var_len;
	int	i;

	if (!argv[1])
		return 0;
	var_len = 0;
	while ((*argv)[var_len] && (*argv)[var_len] != '=')
	{
		var_len++;
		if (!((*argv)[var_len]))
			return (0);
	}
	for (i = 0; envp[i]; i++)
	{
		if (!ft_strncmp(*argv, envp[i], var_len + 1))
			break ;
	}
	if (!envp[i]) // this really shouldn't work
		envp[i + 1] = NULL;
	envp[i] = *argv;
	return 0;
}

int ft_unset(int argc, char **argv, char **envp)
{
	int	var_len;
	int	i;

	var_len = 0;
	if (argc != 2)
		return (0);
	argv++;
	for (i = 0; envp[i]; i++){
		if (!ft_strncmp(*argv, envp[i], var_len + 1))
			break ;
	}
	while (envp[i + 1])
	{
		envp[i] = envp[i+1];
		i++;
	}
	return 0;
}

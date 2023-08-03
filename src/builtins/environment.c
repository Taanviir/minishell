/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/03 17:47:29 by tanas            ###   ########.fr       */
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

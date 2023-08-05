/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/05 13:55:16 by tanas            ###   ########.fr       */
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

int ft_unset(char **argv, char **envp)
{
	int	i;
	int	name_len;
	int	index;

	if (!argv[1])
		return (0);
	i = 0;
	while (envp[++i])
	{
		if (!ft_is_alpha(argv[i][0]) && argv[i][0] != '\"' && argv[i][0] != '\'')
		{
			printf("unset: `%s': not a valid identifier\n", argv[i]);
			continue ;
		}
		name_len = 0;
		while (argv[i][name_len])
			name_len++;
		index = 0;
		while (envp[index] && ft_strncmp(argv[i], envp[index], name_len))
			index++;
		envp[index] = NULL;
	}
	while (envp[i + 1])
	{
		envp[i] = envp[i+1];
		i++;
	}
	return 0;
}

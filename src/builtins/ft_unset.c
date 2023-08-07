/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:59:38 by tanas             #+#    #+#             */
/*   Updated: 2023/08/06 13:59:38 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, t_env **env)
{
	int		i;
	t_env	*temp;

	if (!argv[1])
		return (0);
	i = 0;
	while (argv[++i])
	{
		i += is_name(argv[i][0], argv[i]);
		temp = *env;
		while (temp)
		{
			if (!ft_strncmp(argv[i], temp->name, name_len(argv[i])))
			{
				free_env_node(&temp);
				break ;
			}
			temp = temp->next;
			if (temp == *env)
				break;
		}
	}
	return (0);
}

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

void	free_node_by_name(t_env **env_list, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->name, name, _name(current->name, name)))
		{
			if (!prev)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **argv, t_env **env_list)
{
	int		i;

	if (!argv[1])
		return (0);
	i = 0;
	while (argv[++i])
	{
		if (check_var_unset(argv[i]))
			continue ;
		free_node_by_name(env_list, argv[i]);
	}
	return (0);
}

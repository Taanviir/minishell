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

bool	check_char(char c, char *argv)
{
	if (!ft_is_alpha(c) && c != '\"' && c != '\'')
	{
		printf("export: `%s': not a valid identifier\n", argv);
		return (true);
	}
	return (false);
}

void	free_node_by_name(t_env **env_list, const char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name)))
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
		i += check_char(argv[i][0], argv[i]);
		free_node_by_name(env_list, argv[i]);
	}
	return (0);
}

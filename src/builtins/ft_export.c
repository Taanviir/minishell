/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:47:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/03 17:47:30 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_env_node(t_env *env_list, char *name)
{
	while (env_list)
	{
		if (!ft_strncmp(name, env_list->name, _name(name, env_list->name)))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	ft_export(char **argv, t_env **env_list)
{
	int		i;
	int		ret;
	t_env	*temp;

	if (!argv[1])
		return (print_env_list(env_list), 1);
	i = 0;
	ret = 0;
	while (argv[++i])
	{
		if (check_var_export(argv[i], &ret))
			continue ;
		temp = find_env_node(*env_list, argv[i]);
		if (temp)
		{
			if (ft_strchr(argv[i], '='))
			{
				free(temp->value);
				temp->value = ft_strdup(ft_strchr(argv[i], '=') + 1);
			}
		}
		else
			add_node_bottom(env_list, argv[i]);
	}
	return (ret);
}

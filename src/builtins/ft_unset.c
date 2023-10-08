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

/**
 * @brief checks if the environment variable is valid
 * 
 * @param arg argument to check
 * @return true if error, false if success
 */
bool	check_var_unset(char *arg)
{
	int	i;

	if (!ft_is_alpha(arg[0]) && arg[0] != '_')
	{
		print_env_error(arg, "unset");
		return (true);
	}
	i = 0;
	while (arg[++i])
	{
		if (!ft_is_alnum(arg[i]) && arg[i] != '_')
		{
			print_env_error(arg, "unset");
			return (true);
		}
	}
	return (false);
}

/**
 * @brief frees node by name
 * 
 * @param env_list environment list
 * @param name name of node to free
 */
void	free_node_by_name(t_env **env_list, char *name)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env_list;
	prev = NULL;
	while (cur)
	{
		if (!ft_strncmp(cur->name, name, get_longer_name(cur->name, name)))
		{
			if (!prev)
				*env_list = cur->next;
			else
				prev->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/**
 * @brief unsets environment variable
 * 
 * @param argv arguments
 * @param env_list environment list
 * @return 0 if success, 1 if error
 */
int	ft_unset(char **argv, t_env **env_list)
{
	int	i;
	int	ret;

	ret = 0;
	if (!argv[1])
		return (ret);
	i = 0;
	while (argv[++i])
	{
		if (check_var_unset(argv[i]))
		{
			ret = 1;
			continue ;
		}
		free_node_by_name(env_list, argv[i]);
	}
	return (ret);
}

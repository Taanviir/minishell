/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:50:38 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 17:40:41 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief prints error message for export and unset
 * 
 * @param arg argument to print
 * @param function function name
 */
void	print_env_error(char *arg, char *function)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

/**
 * @brief name length of the environment variable
 * 
 * @param arg argument to get the name length
 * @return length of the name
 */
int	env_name_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

/**
 * @brief finds the longer name of two environment variables
 * 
 * @param var1 environment variable 1
 * @param var2 environment variable 2
 * @return length of the longer name
 */
int	get_longer_name(char *var1, char *var2)
{
	if (env_name_len(var1) > env_name_len(var2))
		return (env_name_len(var1));
	return (env_name_len(var2));
}

t_env	*get_env(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, get_longer_name(env->name, name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:36:53 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 17:36:53 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief get the specific environment variable
 * 
 * @param env_list environment list
 * @param name name of the environment variable
 * @return value of the environment variable
 */
char	*get_env_value(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, name, get_longer_name(env->name, name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief convert environment list to array
 * 
 * @param env_list environment list
 * @return environment array
 */
char	**list_to_array(t_env *env_list)
{
	t_env	*temp;
	int		i;
	char	**env_array;

	i = 0;
	temp = env_list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	i = -1;
	temp = env_list;
	while (temp)
	{
		env_array[++i] = ft_bigjoin(3, temp->name, "=", temp->value);
		temp = temp->next;
	}
	env_array[++i] = NULL;
	return (env_array);
}

/**
 * @brief set the value of the environment variable depeinding on the name
 * 
 * @param var name of the environment variable
 * @param value value of the environment variable
 * @return value of the environment variable
 */
static char	*node_value(char *var, char *value)
{
	char	*check;

	if (!ft_strncmp(var, "SHLVL", env_name_len(var)))
	{
		if (value)
			return (ft_itoa(ft_atoi(value) + 1));
		return (ft_strdup("1"));
	}
	if (!ft_strchr(var, '='))
		return (NULL);
	check = ft_strchr(var, '=') + 1;
	if (!check[0])
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/**
 * @brief add node to the bottom of the list
 * 
 * @param env_list environment list
 * @param env_var environment variable
 */
void	add_node_bottom(t_env **env_list, char *env_var)
{
	t_env	*new_node;
	t_env	*current;
	char	**env_array;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	env_array = ft_split(env_var, '=');
	new_node->name = ft_strdup(env_array[0]);
	new_node->value = node_value(env_var, env_array[1]);
	new_node->next = NULL;
	if (!(*env_list))
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	free_double_ptr((void **) env_array);
}

/**
 * @brief initialize environment list
 * 
 * @param env_list environment list
 * @param envp environment array
 */
void	environment_init(t_env **env_list, char **envp)
{
	int		i;
	t_env	*temp;

	(*env_list) = NULL;
	i = -1;
	while (envp[++i])
		add_node_bottom(env_list, envp[i]);
	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->name, "OLDPWD", 6))
		{
			free(temp->value);
			temp->value = NULL;
		}
		temp = temp->next;
	}
}

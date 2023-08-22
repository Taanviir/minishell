/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/22 21:14:05 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env *env_list, char *name)
{
	while (env_list)
	{
		if (!ft_strncmp(env_list->name, name, _name(env_list->name, name)))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

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

static char	*node_value(char *var, char *value)
{
	char	*check;

	if (!ft_strncmp(var, "SHLVL", name_len(var)))
	{
		if (value)
			return (ft_itoa(ft_atoi(value) + 1));
		else
			return (ft_strdup("1"));
	}
	if (!ft_strchr(var, '=') || !ft_strncmp(var, "OLDPWD", name_len(var)))
		return (NULL);
	check = ft_strchr(var, '=') + 1;
	if (!check[0])
		return (ft_strdup(""));
	return (ft_strdup(value));
}

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
	new_node->equal = 0;
	if (ft_strchr(env_var, '='))
		new_node->equal = 1;
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

void	environment_init(t_env **env_list, char **envp)
{
	int	i;

	(*env_list) = NULL;
	i = -1;
	while (envp[++i])
		add_node_bottom(env_list, envp[i]);
}

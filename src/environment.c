/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/10 19:11:34 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env **env_list, const char *name)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name)))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	free_list(t_env *env)
{
	t_env	*temp;
	t_env	*next;

	temp = env;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
}

char	**list_to_array(t_env *env)
{
	t_env	*temp;
	int		i;
	char	**env_array;

	i = 0;
	temp = env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	i = -1;
	temp = env;
	while (temp)
	{
		env_array[++i] = ft_strjoin(temp->name, "=");
		env_array[i] = ft_strjoin_m(env_array[i], temp->value);
		temp = temp->next;
	}
	env_array[++i] = NULL;
	return (env_array);
}

void	add_node_bottom(t_env **head, char *env_var)
{
	t_env	*new_node;
	t_env	*current;
	char	**env_array;

	env_array = ft_split(env_var, '=');
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free_double_ptr((void **) env_array);
		return ;
	}
	new_node->name = ft_strdup(env_array[0]);
	new_node->value = ft_strdup(env_array[1]);
	new_node->next = NULL;
	if (!(*head))
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	free_double_ptr((void **) env_array);
}

void	environment_init(t_env **env, char **envp)
{
	int	i;

	(*env) = NULL;
	i = -1;
	while (envp[++i])
		add_node_bottom(env, envp[i]);
}

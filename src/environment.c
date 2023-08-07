/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/06 14:00:23 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env **env)
{
	t_env	*temp;

	temp = *env;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	free_env_list(t_env **env)
{
	t_env	*temp;
	t_env	*next;

	temp = *env;
	while (temp->next != *env)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	add_node_bottom(t_env **head, char *envp)
{
	t_env	*new_node;
	char	**env;

	env = ft_split(envp, '=');
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(env[0]);
	new_node->value = ft_strdup(env[1]);
	if (!(*head))
	{
		*head = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else
	{
		new_node->next = *head;
		new_node->prev = (*head)->prev;
		(*head)->prev->next = new_node;
		(*head)->prev = new_node;
	}
	free_double_ptr((void **) env);
}

void	environment_init(t_env **env, char **envp)
{
	int		i;

	(*env) = NULL;
	i = -1;
	while (envp[++i])
		add_node_bottom(env, envp[i]);
}

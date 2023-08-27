/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:07:28 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 13:27:12 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_list(t_env **head)
{
	t_env	*temp;
	t_env	*temp2;
	char	*temp_name;
	char	*temp_value;

	temp = *head;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strncmp(temp->name, temp2->name, ft_strlen(temp->name)) > 0)
			{
				temp_name = temp->name;
				temp_value = temp->value;
				temp->name = temp2->name;
				temp->value = temp2->value;
				temp2->name = temp_name;
				temp2->value = temp_value;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

static char	*get_value(char *value)
{
	if (value)
		return (ft_strdup(value));
	return (NULL);
}

static t_env	*copy_list(t_env *original)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*current;

	new_list = NULL;
	while (original)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(original->name);
		new_node->value = get_value(original->value);
		new_node->next = NULL;
		if (!new_list)
			new_list = new_node;
		else
		{
			current = new_list;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		original = original->next;
	}
	return (new_list);
}

static void	print_export(char *name, char *value)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(name, 1);
	if (value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putendl_fd("", 1);
}

void	print_env_list(t_env **env_list)
{
	t_env	*copy;
	t_env	*temp;

	copy = copy_list(*env_list);
	sort_list(&copy);
	temp = copy;
	while (temp)
	{
		if (!ft_strncmp(temp->name, "_", get_len(temp->name, "_")))
			temp = temp->next;
		if (temp->value)
			print_export(temp->name, temp->value);
		else
			print_export(temp->name, NULL);
		temp = temp->next;
	}
	free_list(copy);
}

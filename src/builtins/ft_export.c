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
		new_node->value = NULL;
		if (original->value)
			new_node->value = ft_strdup(original->value);
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

static void	print_env_list(t_env **env_list)
{
	t_env	*copy;
	t_env	*temp;

	copy = copy_list(*env_list);
	sort_list(&copy);
	temp = copy;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
	free_list(copy);
}

int	ft_export(char **argv, t_env **env_list)
{
	int		i;
	t_env	*temp;

	if (!argv[1])
		return (print_env_list(env_list), 1);
	i = 0;
	while (argv[++i])
	{
		if (check_var_export(argv[i]))
			continue ;
		temp = *env_list;
		while (temp)
		{
			if (!ft_strncmp(argv[i], temp->name, _name(argv[i], temp->name)))
			{
				if (ft_strchr(argv[i], '='))
				{
					free(temp->value);
					temp->value = ft_strdup(ft_strchr(argv[i], '=') + 1);
				}
				break ;
			}
			temp = temp->next;
		}
		if (!temp)
			add_node_bottom(env_list, argv[i]);
	}
	return (0);
}

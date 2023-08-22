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

static void	sort_array(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

// copy and sort linked list instead
static void	print_env_list(t_env **env_list)
{
	char	**temp;
	int		i;
	char	**var;

	temp = list_to_array(*env_list);
	sort_array(temp);
	i = -1;
	while (temp[++i])
	{
		var = ft_split(temp[i], '='); // sets empty var to NULL
		if (ft_strncmp(temp[i], "_=", 2) && var[1])
			printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		if (!var[1])
			printf("declare -x %s\n", var[0]);
		free_double_ptr((void **) var);
	}
	free_double_ptr((void **) temp);
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

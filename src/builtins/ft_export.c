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

/**
 * @brief checks if the environment variable is valid
 * 
 * @param arg argument to check
 * @param ret return value
 * @return true if error, false if success 
 */
bool	check_var_export(char *arg, int *ret)
{
	int	i;

	if (!ft_is_alpha(arg[0]))
	{
		print_env_error(arg, "export");
		*ret = 1;
		return (true);
	}
	i = 0;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_is_alnum(arg[i]) && arg[i] != '_')
		{
			print_env_error(arg, "export");
			*ret = 1;
			return (true);
		}
	}
	return (false);
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
		temp = get_env(*env_list, argv[i]);
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

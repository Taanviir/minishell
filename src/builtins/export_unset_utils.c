/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:50:38 by tanas             #+#    #+#             */
/*   Updated: 2023/08/23 20:55:58 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_msg(char *arg, char *function)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

bool	check_var_unset(char *arg)
{
	int	i;

	if (!ft_is_alpha(arg[0]) && arg[0] != '_')
	{
		print_msg(arg, "unset");
		return (true);
	}
	i = 0;
	while (arg[++i])
	{
		if (!ft_is_alnum(arg[i]) && arg[i] != '_')
		{
			print_msg(arg, "unset");
			return (true);
		}
	}
	return (false);
}

bool	check_var_export(char *arg, int *ret)
{
	int	i;

	if (!ft_is_alpha(arg[0]))
	{
		print_msg(arg, "export");
		*ret = 1;
		return (true);
	}
	i = 0;
	while (arg[++i] && arg[i] != '=')
	{
		if (!ft_is_alnum(arg[i]) && arg[i] != '_')
		{
			print_msg(arg, "export");
			*ret = 1;
			return (true);
		}
	}
	return (false);
}

int	name_len(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	_name(char *var1, char *var2)
{
	if (name_len(var1) > name_len(var2))
		return (name_len(var1));
	return (name_len(var2));
}
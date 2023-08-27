/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:45:02 by tanas             #+#    #+#             */
/*   Updated: 2023/08/19 21:45:02 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

int	print_error(char *err_msg, char *function)
{
	ft_putstr_fd("minishell: ", 2);
	if (function)
		ft_putstr_fd(function, 2);
	ft_putstr_fd(err_msg, 2);
	ft_putendl_fd("", 2);
	return (0);
}

void	close_fds(t_cmd *root)
{
	close(0);
	close(1);
	close(2);
	close(root->open_fd);
}

/**
 * Compares the lengths of the provided variable and environment variable.
 * The function returns the length of the longer of the two.
 *
 * @param lvar_s: The length of the provided variable.
 * @param env_var: The environment variable string in the format "KEY=VALUE".
 *
 * @return: The length of the longer of the two strings (either lvar_s or the
 * length before '=' in env_var).
 */
int	longer(int lvar_s, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	if (i > lvar_s)
		return (i);
	else
		return (lvar_s);
}

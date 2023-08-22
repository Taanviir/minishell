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

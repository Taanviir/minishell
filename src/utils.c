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

// check if the character is a quote
bool is_quote(char c)
{
	return (c == '\'' || c == '"');
}

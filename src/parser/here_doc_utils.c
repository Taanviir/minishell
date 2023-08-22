/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:23:06 by tanas             #+#    #+#             */
/*   Updated: 2023/08/22 15:24:00 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_line(char **line, t_env **env_list)
{
	char	*temp;

	temp = *line;
	*line = expand(*line, *line + ft_strlen(*line), env_list, true);
	free(temp);
}

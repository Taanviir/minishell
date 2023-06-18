/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:47:35 by tanas             #+#    #+#             */
/*   Updated: 2023/04/03 14:38:42 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = malloc(1);
		stash[0] = '\0';
	}
	if (!stash || !buffer)
		return (NULL);
	string = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	i = -1;
	j = 0;
	if (stash)
		while (stash[++i])
			string[i] = stash[i];
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	free(stash);
	return (string);
}

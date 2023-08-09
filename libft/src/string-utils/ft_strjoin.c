/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:47:35 by tanas             #+#    #+#             */
/*   Updated: 2023/07/31 00:16:22 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	string = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		string[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (string);
}

char	*ft_strjoin_m(char *stash, char *buffer)
{
	char	*string;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	string = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		string[i] = stash[i];
		i++;
	}
	free(stash);
	j = 0;
	while (buffer[j])
		string[i++] = buffer[j++];
	string[i] = '\0';
	return (string);
}

char	*ft_bigjoin(int count, ...)
{
	va_list	args;
	char	*result;
	int		i;

	va_start(args, count);
	result = NULL;
	i = -1;
	while (++i < count)
		result = ft_strjoin_m(result, va_arg(args, char *));
	va_end(args);
	return (result);
}

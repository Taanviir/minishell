/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:56:18 by tanas             #+#    #+#             */
/*   Updated: 2022/11/22 13:06:57 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;

	i = 0;
	h = (char *) haystack;
	if (!ft_strlen(needle) || haystack == needle)
		return (h);
	while (len-- && h[i])
	{
		j = 0;
		while (h[i + j] && needle[j] && h[i + j] == needle[j] && j <= len)
			j++;
		if (!needle[j])
			return (&h[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:38 by tanas             #+#    #+#             */
/*   Updated: 2022/12/11 14:05:18 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (!size && ((SIZE_MAX / size) < count))
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, size * count);
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:41:08 by tanas             #+#    #+#             */
/*   Updated: 2023/03/26 16:33:40 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 returned if no alphabet found and 1 returned if alphabet is found
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')));
}

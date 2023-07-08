/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:41:08 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:57:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 returned if no alphabet found and 1 returned if alphabet is found
bool	ft_is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:49:05 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:57:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 returned if no ascii char found and 1 returned if found
bool	ft_is_ascii(int c)
{
	return (c >= 0 && c <= 127);
}

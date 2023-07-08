/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:28:15 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:57:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 returned if no digit found and 1 returned if digit found
bool	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

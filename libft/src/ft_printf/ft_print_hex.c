/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:04:04 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:54:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int n, char *base)
{
	int	length_of_print;

	length_of_print = 0;
	if (n > 15)
		length_of_print += ft_print_hex(n / 16, base);
	length_of_print += write(1, &base[n % 16], 1);
	return (length_of_print);
}

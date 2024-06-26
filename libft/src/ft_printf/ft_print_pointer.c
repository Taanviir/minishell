/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:04:08 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:53:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer(size_t pointer, char *base)
{
	int	length_of_print;

	length_of_print = 0;
	if (pointer > 15)
		length_of_print += ft_print_pointer(pointer / 16, base);
	length_of_print += write(1, &base[pointer % 16], 1);
	return (length_of_print);
}

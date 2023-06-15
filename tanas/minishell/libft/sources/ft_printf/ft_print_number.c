/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:44:42 by tanas             #+#    #+#             */
/*   Updated: 2022/12/17 14:01:26 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_number(int n)
{
	char	*number_as_string;
	int		length_of_print;

	number_as_string = ft_itoa(n);
	length_of_print = ft_print_string(number_as_string);
	free(number_as_string);
	return (length_of_print);
}

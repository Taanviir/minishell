/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:23:06 by tanas             #+#    #+#             */
/*   Updated: 2023/01/08 14:52:30 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

// printf functions
int		ft_printf(const char *str, ...);
int		ft_print_char(const char c);
int		ft_print_string(char *str);
int		ft_print_number(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, char *base);
int		ft_print_pointer(size_t pointer, char *base);

#endif
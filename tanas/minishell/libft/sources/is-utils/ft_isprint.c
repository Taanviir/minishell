/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:53:46 by tanas             #+#    #+#             */
/*   Updated: 2023/03/26 16:33:12 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 returned if no printable char found and 1 returned if found
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

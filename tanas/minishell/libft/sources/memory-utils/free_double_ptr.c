/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:26:04 by tanas             #+#    #+#             */
/*   Updated: 2023/05/25 16:26:23 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_ptr(void **double_ptr)
{
	int	i;

	if (!double_ptr || !(*double_ptr))
		return ;
	i = 0;
	while (double_ptr[i])
	{
		free(double_ptr[i]);
		i++;
	}
	free(double_ptr);
}

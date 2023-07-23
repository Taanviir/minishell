/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 03:17:30 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/20 13:54:06 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int	var_len;
	int	i;

	var_len = 0;
	if (argc != 2)
		return (0);
	argv++;
	for (i = 0; envp[i]; i++){
		if (!ft_strncmp(*argv, envp[i], var_len + 1))
			break ;
	}
	while (envp[i + 1])
	{
		envp[i] = envp[i+1];
		i++;
	}
}

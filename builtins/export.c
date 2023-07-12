/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 03:46:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/13 02:27:39 by sabdelra         ###   ########.fr       */
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
	while ((*argv)[var_len] && (*argv)[var_len] != '=') {
		var_len++;
		if (!((*argv)[var_len]))
			return (0);
	}
	for (i = 0; envp[i]; i++){
		if (!ft_strncmp(*argv, envp[i], var_len + 1))
			break ;
	}
	if (!envp[i]) // this really shouldn't work
		envp[i + 1] = NULL;
	envp[i] = *argv;
}

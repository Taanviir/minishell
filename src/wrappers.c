/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:39:08 by tanas             #+#    #+#             */
/*   Updated: 2023/08/16 17:46:27 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg);

int	wfork(void)
{
	int	pid;

	signal(SIGINT, sigint_handle);
	pid = fork();
	if (pid == -1)
		perror("");
	return (pid);
}
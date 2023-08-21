/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:39:08 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 12:28:56 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wfork(void)
{
	int	pid;

	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
	pid = fork();
	if (pid == -1)
		perror("");
	return (pid);
}

/**
 * @brief Checks if a pipe was created successfully.
 *
 * In case of an error during pipe creation, prints the error.
 *
 * @param pipe_return The return value from the pipe() system call.
 * @return true if the pipe was created successfully, false otherwise.
 */
bool	verify_pipe(int pipe_return)
{
	if (pipe_return < 0)
	{
		perror("");
		return (false);
	}
	return (true);
}
// TODO wrappers for dup and close failures

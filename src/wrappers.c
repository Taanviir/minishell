/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:39:08 by tanas             #+#    #+#             */
/*   Updated: 2023/08/18 19:38:44 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: use this function
void	print_error(char *msg);

int	wfork(void)
{
	int	pid;

	signal(SIGINT, sigint_handler_child);
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

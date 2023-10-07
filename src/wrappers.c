/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:39:08 by tanas             #+#    #+#             */
/*   Updated: 2023/10/07 16:35:18 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sets the child signal handler and forks a child process.
 * @return the pid of the child process.
 */
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

/**
 * @brief Checks if a file was opened successfully.
 *
 * In case of an error during file opening, prints the error.
 *
 * @param fd The file descriptor returned by the open() system call.
 * @param file_path The path of the file that was opened.
 * @return true if the file was opened successfully, false otherwise.
 */
bool	verify_open(const int fd, const char *file_path)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file_path);
		return (false);
	}
	return (true);
}

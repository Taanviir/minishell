/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:34:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/21 12:29:26 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle file open failures.
static bool	verify_file_opened(const int fd, const char *file_path)
{
	if (fd < 0)
	{
		write(2, "minishell: ", 12);
		perror(file_path);
		return (false);
	}
	return (true);
}
/**
 * Executes a command with stream redirection.
 *
 * The function manages stream redirection for both input and output. It replaces the
 * standard in/out (as required) with the provided file descriptor, executes the command,
 * and then restores the standard in/out.
 *
 * @param cmd      A structure holding command details.
 * @param env_list	Linked list of environment variables.
 */
void	execute_redir(t_cmd *cmd, t_env **env_list)
{
	t_redircmd	*redircmd;
	int			new_fd;
	int			save_fd;

	// Typecast the cmd structure to access redirection-specific parameters.
	redircmd = (t_redircmd *)cmd;
	// Save the previous standard in/out for restoration after command execution.
	save_fd = dup(redircmd->fd);
	// If here_doc flag is set, use the here_doc pipe, else open the required file.
	if (redircmd->here_doc)
		new_fd = redircmd->here_doc;
	else
		new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
	if (!verify_file_opened(new_fd, redircmd->fp))
		return ;
	// Replace the original file descriptor with the new one.
	dup2(new_fd, redircmd->fd);
	// Close the new file descriptor, could be a pipe read or a file.
	close(new_fd);
	// Execute the actual command with redirection in place.
	runcmd(redircmd->cmd, env_list);
	// Restore the original file descriptor.
	dup2(save_fd, redircmd->fd);
	close(save_fd);
}

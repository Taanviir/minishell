/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 19:38:24 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle file open failures.
static bool	verify_file_opened(const int fd, const char *file_path)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file_path);
		return (false);
	}
	return (true);
}

//WIP recursive call to reproduce bash's opening order
t_cmd	*depth_first_open(t_redircmd *redircmd, int *new_fd, t_redircmd *top)
{
	t_cmd	*rcmd;
	// Base case: If the current node is not a redirection node or does not fit the condition
	if (redircmd->cmd->type != REDIR || !(((t_redircmd *)redircmd->cmd)->fd == redircmd->fd))
	{
		if (redircmd->here_doc)
			*new_fd = redircmd->here_doc;
		else if (!redircmd->mode)
			*new_fd = open(redircmd->fp, redircmd->mode);
		else
			*new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
		if (!verify_file_opened(*new_fd, redircmd->fp))
		{
			close(*new_fd);
			return (NULL); // Error occurred
		}
		if (redircmd != top)
			close (*new_fd);
		return (redircmd->cmd); // Return success without opening
	}
	// Recursive call
	rcmd = depth_first_open((t_redircmd *)redircmd->cmd, new_fd, top);
	if (!rcmd)
	{
		// g_exit_status = 1 << 8;
		return (NULL); // If any error occurred down the line, propagate it up
	}
	if (redircmd->here_doc)
		*new_fd = redircmd->here_doc;
	else if (!redircmd->mode)
		*new_fd = open(redircmd->fp, redircmd->mode);
	else
		*new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
	if (!verify_file_opened(*new_fd, redircmd->fp))
	{
		close(*new_fd);
		return (NULL); // Error occurred
	}
	if (redircmd != top)
		close(*new_fd);
	return (rcmd); // Success
}

/**
 * Executes a command with stream redirection.
 *
 * The function manages stream redirection for both input and output.
 * It replaces the standard in/out (as required) with the provided file
 * descriptor, executes the command, and then restores the standard in/out.
 *
 * @param cmd      A structure holding command details.
 * @param env_list	Linked list of environment variables.
 */
void	execute_redir(t_cmd *cmd, t_env **env_list, t_cmd *root)
{
	t_redircmd	*redircmd;
	int			new_fd;
	int			save_fd;
	t_cmd		*rcmd;

	redircmd = (t_redircmd *)cmd;
	save_fd = dup(redircmd->fd);
	// if (redircmd->here_doc)
	// 	new_fd = redircmd->here_doc;
	// else
	// 	new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
	rcmd = depth_first_open(redircmd, &new_fd, redircmd);
	if (!rcmd)
		g_exit_status = 1 << 8;
	// if (!verify_file_opened(new_fd, redircmd->fp))
	// {
	// 	close(save_fd);
	// 	close(new_fd);
	// 	return ;
	// }
	root->open_fd = new_fd;
	dup2(new_fd, redircmd->fd);
	close(new_fd);
	runcmd(rcmd, env_list, root);
	dup2(save_fd, redircmd->fd);
	close(save_fd);
}

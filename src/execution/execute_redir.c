/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 00:35:14 by sabdelra         ###   ########.fr       */
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

// WIP recursive call to reproduce bash's opening order
//t_cmd	*depth_first_open(t_redircmd *redircmd) {
//	int	tmp_fd;

//	// Base case: If the current node is not a redirection node or does not fit the condition
//	if (redircmd->cmd->type != REDIR || !(((t_redircmd *)redircmd->cmd)->fd == redircmd->fd))
//		return (redircmd->cmd); // Return success without opening
//	// Recursive call
//	if (!depth_first_open((t_redircmd *)redircmd->cmd))
//		return (NULL); // If any error occurred down the line, propagate it up
//	tmp_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
//	if (!verify_file_opened(tmp_fd, redircmd->fp)) {
//		close(tmp_fd);
//		return (NULL); // Error occurred
//	}
//	close(tmp_fd);
//	return (redircmd->cmd); // Success
//}

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
	int			tmp_fd;
	int			save_fd;

	redircmd = (t_redircmd *)cmd;
	save_fd = dup(redircmd->fd);
	if (redircmd->here_doc)
		new_fd = redircmd->here_doc;
	else
		new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
	// this loop has to be done recursively, to reproduce the exact behaviour
	while (redircmd->cmd->type == REDIR && ((t_redircmd *)redircmd->cmd)->fd == redircmd->fd)
	{
		redircmd = (t_redircmd *)redircmd->cmd;
		if (redircmd->here_doc)
			tmp_fd = redircmd->here_doc;
		else
			tmp_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
		if (!verify_file_opened(tmp_fd, redircmd->fp))
		{
			close(save_fd);
			close(new_fd);
			close(tmp_fd);
			return ;
		}
		close(tmp_fd);
	}
	if (!verify_file_opened(new_fd, redircmd->fp))
	{
		close(save_fd);
		close(new_fd);
		return ;
	}
	root->open_fd = new_fd;
	dup2(new_fd, redircmd->fd);
	close(new_fd);
	runcmd(redircmd->cmd, env_list, root);
	dup2(save_fd, redircmd->fd);
	close(save_fd);
}

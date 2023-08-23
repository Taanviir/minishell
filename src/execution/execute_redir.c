/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/23 23:53:47 by sabdelra         ###   ########.fr       */
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

// Recursive function to open and discard all output redirections
// t_redircmd	*depth_first(t_redircmd *redircmd)
// {
// 	int			tmp_fd;
// 	t_redircmd	*deepest_redircmd;
// 	// t_redircmd *old_redircmd;
// 	deepest_redircmd = redircmd;
// 	//old_redircmd = NULL;
// 	if (redircmd->cmd->type == REDIR && (redircmd->fd == 1 && ((t_redircmd *)redircmd->cmd)->fd == redircmd->fd))
// 	{
// 		//old_redircmd = (t_redircmd *)redircmd->cmd;
// 		// Recursive call to find the deepest valid redirection node
// 		deepest_redircmd = depth_first((t_redircmd *)redircmd->cmd);
// 		// Reassign this deepest node to be the direct child of the current node
// 		redircmd->cmd = (t_cmd *)deepest_redircmd;
// 	}
// 	tmp_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
// 	if (!verify_file_opened(tmp_fd, redircmd->fp))
// 	{
// 		close(tmp_fd);
// 		return (NULL); // Signal an error using NULL
// 	}
// 	//if (old_redircmd)
// 	//	free(old_redircmd); // specifically not calling free_tree() here, not to free the cmd under it
// 	close(tmp_fd);
// 	return (deepest_redircmd);
// }

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
	runcmd(redircmd->cmd, env_list, root); //! the dup save_fd is not being closed inside the forked process
	dup2(save_fd, redircmd->fd);
	close(save_fd);
}

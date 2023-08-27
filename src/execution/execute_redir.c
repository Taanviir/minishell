/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/27 13:17:55 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle file open failures.


static bool	input_redirection(t_redircmd *rcmd, int *fd)
{
	int	tmp_fd;

	tmp_fd = *fd;
	if (!rcmd->here_doc)
		*fd = open(rcmd->filename, rcmd->mode, rcmd->permissions);
	else
		*fd = rcmd->here_doc;
	if (tmp_fd != ERROR)
		close(tmp_fd);
	if (!verify_open(*fd, rcmd->filename))
		return (false);
	return (true);
}

static bool	output_redirection(t_redircmd *rcmd, int *fd)
{
	int	tmp_fd;

	tmp_fd = *fd;
	*fd = open(rcmd->filename, rcmd->mode, rcmd->permissions);
	if (tmp_fd != ERROR)
		close(tmp_fd);
	if (!verify_open(*fd, rcmd->filename))
		return (false);
	return (true);
}

t_cmd	*depth_first_open(t_redircmd *rcmd, int *new_fd, t_redircmd *top)
{
	t_cmd	*cmd;

	if (rcmd->type != REDIR)
		return ((t_cmd *)rcmd);
	else
		cmd = depth_first_open((t_redircmd *)rcmd->cmd, new_fd, top);
	if (!cmd)
		return (NULL);
	else if (rcmd->FD == IN)
	{
		if (!input_redirection(rcmd, &new_fd[IN]))
			return (NULL);
	}
	else if (rcmd->FD == OUT)
	{
		if (!output_redirection(rcmd, &new_fd[OUT]))
			return (NULL);
	}
	return (cmd);
}

// if new_fd was set the redirection and save the old one
static int	duplicate_fd(int *new_fd, int stream)
{
	int	tmp_fd;

	tmp_fd = 0;
	if (*new_fd > ERROR)
	{
		tmp_fd = dup(stream);
		dup2(*new_fd, stream);
		close(*new_fd);
	}
	return (tmp_fd);
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
void	execute_redir(t_cmd *rcmd, t_env **env_list, t_cmd *root)
{
	t_redircmd	*redircmd;
	int			new_fd[2];
	int			save_fd[2];
	t_cmd		*cmd;

	new_fd[IN] = ERROR;
	new_fd[OUT] = ERROR;
	redircmd = (t_redircmd *)rcmd;
	cmd = depth_first_open(redircmd, new_fd, redircmd);
	save_fd[IN] = duplicate_fd(&new_fd[IN], STDIN_FILENO);
	save_fd[OUT] = duplicate_fd(&new_fd[OUT], STDOUT_FILENO);
	if (!cmd)
		g_exit_status = 1 << 8;
	runcmd(cmd, env_list, root);
	if (new_fd[IN] != ERROR)
	{
		dup2(save_fd[IN], STDIN_FILENO);
		close(save_fd[IN]);
	}
	if (new_fd[OUT] != ERROR)
	{
		dup2(save_fd[OUT], STDOUT_FILENO);
		close(save_fd[OUT]);
	}
}

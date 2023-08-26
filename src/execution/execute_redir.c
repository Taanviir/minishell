/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/27 02:02:23 by sabdelra         ###   ########.fr       */
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
t_cmd	*depth_first_open(t_redircmd *rcmd, int *new_fd, t_redircmd *top)
{
	t_cmd	*cmd;
	int		tmp_fd;
	// Base case
	if (rcmd->type != REDIR)
		return ((t_cmd *)rcmd); // not a redirection node
	else
		cmd = depth_first_open((t_redircmd *)rcmd->cmd, new_fd, top);
	if (!cmd)
		return (NULL);
	if (rcmd->FD == IN)
	{
		tmp_fd = new_fd[IN];
		if (!rcmd->here_doc)
			new_fd[IN] = open(rcmd->filename, rcmd->mode, rcmd->permissions);
		else
			new_fd[IN] = rcmd->here_doc;
		if (tmp_fd != ERROR)
			close(tmp_fd);
		if (!verify_file_opened(new_fd[IN], rcmd->filename))
			return (NULL);
	}
	else if (rcmd->FD == OUT)
	{
		tmp_fd = new_fd[OUT];
		new_fd[OUT] = open(rcmd->filename, rcmd->mode, rcmd->permissions);
		if (tmp_fd != ERROR)
			close(tmp_fd);
		if (!verify_file_opened(new_fd[OUT], rcmd->filename))
			return (NULL);
	}
	return (cmd);
}

// if new_fd was set the redirection and save the old one
static int duplicate_fd(int *new_fd, int stream)
{
	int	tmp_fd;
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
	int			new_fd[2]; // for IN, OUT
	int			save_fd[2]; // save the old FDs to open it back after redirection
	t_cmd		*cmd;

	// start off with an ERROR state indicating that FD is not set
	new_fd[IN] = ERROR;
	new_fd[OUT] = ERROR;
	redircmd = (t_redircmd *)rcmd;
	cmd = depth_first_open(redircmd, new_fd, redircmd); // here we get the final cmd
	// if new_fd was set the redirection and save the old one
	save_fd[IN] = duplicate_fd(&new_fd[IN], STDIN_FILENO);
	save_fd[OUT] = duplicate_fd(&new_fd[OUT], STDOUT_FILENO);
	// means an error in redirection occured
	if (!cmd)
		g_exit_status = 1;
	/* root->open_fd = new_fd; */
	runcmd(cmd, env_list, root);
	// return the old fds back
	if (new_fd[IN] != ERROR)
		dup2(save_fd[IN], STDIN_FILENO);
	if (new_fd[OUT] != ERROR)
		dup2(save_fd[OUT], STDOUT_FILENO);
	close(save_fd[IN]);
	close(save_fd[OUT]);
}



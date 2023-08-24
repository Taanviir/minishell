/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:21:30 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 21:27:10 by sabdelra         ###   ########.fr       */
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

// static int	open_file(t_redircmd *redircmd, int *new_fd)
// {
// 	if (redircmd->here_doc)
// 		*new_fd = redircmd->here_doc;
// 	else if (!redircmd->mode)
// 		*new_fd = open(redircmd->fp, redircmd->mode);
// 	else
// 		*new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
// 	if (!verify_file_opened(*new_fd, redircmd->fp))
// 		return (close(*new_fd), 0);
// 	return (1);
// }

// if (redircmd->cmd->type != REDIR
//|| !(((t_redircmd *)redircmd->cmd)->fd == redircmd->fd))
//WIP recursive call to reproduce bash's opening order
// t_cmd	*depth_first_open(t_redircmd *redircmd,
//int *new_fd, t_redircmd *top)
// {
// 	t_cmd	*rcmd;

// 	if (redircmd->cmd->type != REDIR)
// 	{
// 		if (!open_file(redircmd, new_fd))
// 			return (NULL);
// 		if (redircmd != top)
// 			close (*new_fd);
// 		return (redircmd->cmd);
// 	}
// 	rcmd = depth_first_open((t_redircmd *)redircmd->cmd, new_fd, top);
// 	if (!rcmd)
// 		return (NULL);
// 	if (!open_file(redircmd, new_fd))
// 		return (NULL);
// 	if (redircmd != top)
// 		close (*new_fd);
// 	return (rcmd);
// }

static int	v(int save_fd, int new_fd, int tmp_fd)
{
	close(save_fd);
	close(new_fd);
	if (tmp_fd)
		close(tmp_fd);
	g_exit_status = 1 << 8;
	return (0);
}

static void	stuff(t_redircmd *rcmd, t_env **env_list, t_cmd *root, int *fd)
{
	root->open_fd = fd[0];
	dup2(fd[0], rcmd->fd);
	close(fd[0]);
	runcmd(rcmd->cmd, env_list, root);
	dup2(fd[1], rcmd->fd);
	close(fd[1]);
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
	t_redircmd	*rcmd;
	int			fd[2];
	int			tfd;

	rcmd = (t_redircmd *)cmd;
	fd[1] = dup(rcmd->fd);
	if (rcmd->here_doc)
		fd[0] = rcmd->here_doc;
	else
		fd[0] = open(rcmd->fp, rcmd->mode, S_IRUSR | S_IWUSR);
	while (rcmd->cmd->type == REDIR
		&& ((t_redircmd *)rcmd->cmd)->fd == rcmd->fd)
	{
		rcmd = (t_redircmd *)rcmd->cmd;
		if (rcmd->here_doc)
			tfd = rcmd->here_doc;
		else
			tfd = open(rcmd->fp, rcmd->mode, S_IRUSR | S_IWUSR);
		if (!verify_file_opened(tfd, rcmd->fp) && !v(fd[1], fd[0], tfd))
			return ;
		close(tfd);
	}
	if (!verify_file_opened(fd[0], rcmd->fp) && !v(fd[1], fd[0], 0))
		return ;
	stuff(rcmd, env_list, root, fd);
}

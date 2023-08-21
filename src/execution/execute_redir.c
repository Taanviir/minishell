/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:34:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/21 23:40:47 by sabdelra         ###   ########.fr       */
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

	redircmd = (t_redircmd *)cmd;
	save_fd = dup(redircmd->fd);
	if (redircmd->here_doc)
		new_fd = redircmd->here_doc;
	else
		new_fd = open(redircmd->fp, redircmd->mode, S_IRUSR | S_IWUSR);
	if (!verify_file_opened(new_fd, redircmd->fp))
		return ;
	dup2(new_fd, redircmd->fd);
	close(new_fd);
	runcmd(redircmd->cmd, env_list, root);
	dup2(save_fd, redircmd->fd);
	close(save_fd);
}

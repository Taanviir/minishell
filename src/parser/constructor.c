/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva-1 <eva-1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:13:29 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/08 01:27:38 by eva-1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* Constructors */
//! all constructors malloc */
t_cmd	*construct_exec(void)
{
	t_exec	*cmd;

	cmd = ft_calloc(sizeof(t_exec), 1);
	cmd->expanded = ft_calloc(sizeof(bool), ARGC);
	cmd->argv = ft_calloc(sizeof(char *), ARGC);
	cmd->eargv = ft_calloc(sizeof(char *), ARGC);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_redircmd(t_cmd *command, char *fp, char *efp, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = ft_calloc(sizeof(t_redircmd), 1);
	cmd->type = REDIR;
	cmd->cmd = command;
	if (fp == 0) //! here_doc case
		cmd->here_doc = *(int *)efp; // read_end of the pipe
	else {
		cmd->fp = fp;
		cmd->efp = efp;
	}
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *) cmd);
}

t_cmd	*construct_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(sizeof(t_pipecmd), 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
}

t_cmd	*construct_seqcmd(t_cmd *left, t_cmd *right)
{
	t_seqcmd	*cmd;

	cmd = ft_calloc(sizeof(t_seqcmd), 1);
	cmd->type = SEQUENCE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
}

t_cmd	*construct_bgcmd(t_cmd *cmd)
{
	t_bgcmd	*bgcmd;

	bgcmd = ft_calloc(sizeof(t_bgcmd), 1);
	bgcmd->type = BG;
	bgcmd->cmd = cmd;
	return ((t_cmd *) bgcmd);
}

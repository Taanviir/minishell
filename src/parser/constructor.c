/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:13:29 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/07 03:18:42 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/* Constructors */
//! all constructors malloc */
t_cmd	*construct_exec(void)
{
	t_exec	*cmd;

	cmd = ft_calloc(sizeof(t_exec), 1);
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
	cmd->fp = fp;
	cmd->efp = efp;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(sizeof(t_pipecmd), 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_seqcmd(t_cmd *left, t_cmd *right)
{
	t_seqcmd	*cmd;

	cmd = ft_calloc(sizeof(t_seqcmd), 1);
	cmd->type = SEQUENCE;
	cmd->left = left;
	cmd->right = right;
	return((t_cmd *)cmd);
}

t_cmd	*construct_bgcmd(t_cmd *cmd)
{
	t_bgcmd	*bgcmd;

	bgcmd = ft_calloc(sizeof(t_bgcmd), 1);
	bgcmd->type = BG;
	bgcmd->cmd = cmd;
	return((t_cmd *)bgcmd);
}

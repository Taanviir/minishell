/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:13:29 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/21 14:43:43 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Constructors */
t_cmd	*construct_exec(void)
{
	t_exec	*cmd;

	cmd = ft_calloc(sizeof(t_exec), 1);
	cmd->argv = ft_calloc(sizeof(char *), ARGC);
	cmd->eargv = ft_calloc(sizeof(char *), ARGC);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_redircmd(t_cmd *cmd, char *fp, char *efp, int *oc)
{
	t_redircmd	*redircmd;

	redircmd = ft_calloc(sizeof(t_redircmd), 1);
	redircmd->type = REDIR;
	redircmd->cmd = cmd;
	if (fp == 0)
		redircmd->here_doc = *(int *)efp;
	else
	{
		redircmd->fp = fp;
		redircmd->efp = efp;
	}
	redircmd->mode = oc[MODE];
	redircmd->fd = oc[FD];
	free(oc);
	return ((t_cmd *) redircmd);
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

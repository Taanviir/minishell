/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:13:29 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/26 15:08:33 by sabdelra         ###   ########.fr       */
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

t_cmd	*construct_redircmd(t_cmd *cmd, char *fp, int *oc)
{
	t_redircmd	*redircmd;

	redircmd = ft_calloc(sizeof(t_redircmd), 1);
	redircmd->type = REDIR;
	redircmd->cmd = cmd;
	if (fp)
		redircmd->filename= fp;
	redircmd->mode = oc[MODE];
	redircmd->FD= oc[FD];
	redircmd->permissions= oc[PERMISSIONS];
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:55:59 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/13 00:42:04 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_cmd(t_cmd *cmd)
{
	t_exec *exec;
	size_t	i;

	exec = (t_exec *)cmd;
	i = 0;
	while (i < exec->argc) {
		if (exec->expanded[i])
			free(exec->argv[i]);
		i++;
	}
	free(exec->expanded);
	free(exec->argv);
	free(exec->eargv);
	free(exec);
}

void	free_redir(t_cmd *cmd)
{
	t_redircmd *redir;

	redir = (t_redircmd *)cmd;
	free_tree(redir->cmd);
	free(redir);
}

void	free_pipe(t_cmd *cmd)
{
	t_pipecmd *pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	free_tree(pipecmd->left);
	free_tree(pipecmd->right);
	free(pipecmd);
}

void	free_seq(t_cmd *cmd)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	free_tree(seqcmd->left);
	free_tree(seqcmd->right);
	free(seqcmd);
}

void	free_bgcmd(t_cmd *cmd)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	free_tree(bgcmd->cmd);
	free(bgcmd);
}

typedef void (*t_free)(t_cmd *cmd);

void free_tree(t_cmd *cmd)
{
	t_free tree_free[5];

	tree_free[0] = free_cmd;
	tree_free[1] = free_redir;
	tree_free[2] = free_pipe;
	tree_free[3] = free_seq;
	tree_free[4] = free_bgcmd;
	if (!cmd)
		return ;
	tree_free[cmd->type](cmd);
}

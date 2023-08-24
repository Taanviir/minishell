/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:55:59 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/24 17:34:35 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_cmd *cmd)
{
	t_redircmd	*redir;

	redir = (t_redircmd *)cmd;
	free(redir->fp);
	free_tree(redir->cmd);
	free(redir);
}

void	free_pipe(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	free_tree(pipecmd->left);
	free_tree(pipecmd->right);
	free(pipecmd);
}

typedef void	(*t_free)(t_cmd *cmd);

void	free_tree(t_cmd *cmd)
{
	t_free	tree_free[3];

	tree_free[0] = free_cmd;
	tree_free[1] = free_redir;
	tree_free[2] = free_pipe;
	if (!cmd)
		return ;
	tree_free[cmd->type](cmd);
}

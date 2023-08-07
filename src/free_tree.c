/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:55:59 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/07 21:23:24 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_cmd(t_cmd *cmd)
{
	t_exec *exec;

	exec = (t_exec *)cmd;
	//! if one of the argv's is expanded it should be freed here need a flag for expanded
	free(exec->argv);
	free(exec->eargv);
	free(exec);
}


typedef void (*t_free)(t_cmd *cmd);

void free_tree(t_cmd *cmd)
{
	t_free tree_free[1];

	tree_free[0] = free_cmd;
	// tree_free[1] = free_redir;
	// tree_free[2] = free_pipe;
	// tree_free[3] = free_seq;
	// tree_free[4] = free_bgcmd;
	if (!cmd)
		return;
	tree_free[cmd->type](cmd);
}

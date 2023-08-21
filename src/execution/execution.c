/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 14:41:58 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_bg(void)
{
	char	*pid;

	pid = ft_itoa((int)getpid());
	printf("[%i] %s\n", 1, pid);
}

static void	execute_bgcmd(t_cmd *cmd, t_env **env_list)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!wfork())
	{
		write_bg();
		runcmd(bgcmd->cmd, env_list);
		free_tree(cmd);
		exit(0);
	}
}

static void	execute_seq(t_cmd *cmd, t_env **env_list)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	if (!wfork())
	{
		runcmd(seqcmd->left, env_list);
		free_tree(cmd);
		exit(0);
	}
	wait(NULL);
	runcmd(seqcmd->right, env_list);
}

typedef void	(*t_execute)(t_cmd *cmd, t_env **env_list);

t_cmd	*runcmd(t_cmd *cmd, t_env **env_list)
{
	t_execute	executers[5];

	executers[0] = execute_cmd;
	executers[1] = execute_redir;
	executers[2] = execute_pipe;
	executers[3] = execute_seq;
	executers[4] = execute_bgcmd;
	if (!cmd)
		return (NULL);
	executers[cmd->type](cmd, env_list);
	return (cmd);
}

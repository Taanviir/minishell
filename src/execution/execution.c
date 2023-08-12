/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/12 20:12:48 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO maybe doesn't belong here, maybe libft or a more global file
int	get_len(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (ft_strlen(str1));
	return (ft_strlen(str2));
}

static void	write_bg(void)
{
	char *pid;

	pid = ft_itoa((int)getpid());
	write(1, "[1] ", 4); // TODO update the number of bg processes
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
}

//! handle printf &
static void	execute_bgcmd(t_cmd *cmd, t_env **env_list)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	if (!fork())
	{
		write_bg();
		runcmd(bgcmd->cmd, env_list);
		free_tree(cmd);
		exit(0);
	}
	// wait(0);
}
/* TODO some missing behaviour how to call back to fg and update number */

static void	execute_seq(t_cmd *cmd, t_env **env_list)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	if (!fork())
	{
		runcmd(seqcmd->left, env_list);
		free_tree(cmd);
		exit(0);
	}
	wait(NULL);
	runcmd(seqcmd->right, env_list);
}

typedef void (*t_execute)(t_cmd *cmd, t_env **env_list);

t_cmd *runcmd(t_cmd *cmd, t_env **env_list)
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
	return(cmd);
}

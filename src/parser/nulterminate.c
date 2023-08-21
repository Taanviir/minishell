/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:27:36 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 16:39:26 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nullterminate_redir(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)cmd;
	nullterminate(redircmd->cmd);
	if (redircmd->fp)
		*redircmd->efp = 0;
}

static void	nullterminate_pipe(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	nullterminate(pipecmd->left);
	nullterminate(pipecmd->right);
}

static void	nullterminate_seq(t_cmd *cmd)
{
	t_seqcmd	*seqcmd;

	seqcmd = (t_seqcmd *)cmd;
	nullterminate(seqcmd->left);
	nullterminate(seqcmd->right);
}

static void	nullterminate_bgcmd(t_cmd *cmd)
{
	t_bgcmd	*bgcmd;

	bgcmd = (t_bgcmd *)cmd;
	nullterminate(bgcmd->cmd);
}

typedef void	(*t_nullterm)(t_cmd *cmd);

t_cmd	*nullterminate(t_cmd *cmd)
{
	t_nullterm	nullterminators[5];

	nullterminators[0] = NULL;
	nullterminators[1] = nullterminate_redir;
	nullterminators[2] = nullterminate_pipe;
	nullterminators[3] = nullterminate_seq;
	nullterminators[4] = nullterminate_bgcmd;
	if (!cmd)
		return (NULL);
	if (!cmd->type)
		return (cmd);
	nullterminators[cmd->type](cmd);
	return (cmd);
}

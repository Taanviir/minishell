/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:27:36 by tanas             #+#    #+#             */
/*   Updated: 2023/08/26 15:28:38 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nullterminate_redir(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)cmd;
	nullterminate(redircmd->cmd);
}

static void	nullterminate_pipe(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	nullterminate(pipecmd->left);
	nullterminate(pipecmd->right);
}


typedef void	(*t_nullterm)(t_cmd *cmd);

t_cmd	*nullterminate(t_cmd *cmd)
{
	t_nullterm	nullterminators[3];

	nullterminators[0] = NULL;
	nullterminators[1] = nullterminate_redir;
	nullterminators[2] = nullterminate_pipe;
	if (!cmd)
		return (NULL);
	if (!cmd->type)
		return (cmd);
	nullterminators[cmd->type](cmd);
	return (cmd);
}

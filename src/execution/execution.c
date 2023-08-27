/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 17:33:27 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef void	(*t_execute)(t_cmd *cmd, t_env **env_list, t_cmd *root);

t_cmd	*runcmd(t_cmd *cmd, t_env **env_list, t_cmd *root)
{
	t_execute	executers[3];

	executers[0] = execute_cmd;
	executers[1] = execute_redir;
	executers[2] = execute_pipe;
	if (!cmd)
		return (NULL);
	executers[cmd->type](cmd, env_list, root);
	return (cmd);
}

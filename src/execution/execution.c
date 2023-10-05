/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:24:32 by tanas             #+#    #+#             */
/*   Updated: 2023/10/05 17:19:03 by sabdelra         ###   ########.fr       */
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

void	cleanup_exec(char *fp, t_cmd *root, char **env, t_env *env_list)
{
	free(fp);
	close_fds(root);
	free_double_ptr((void **) env);
	free_tree(root);
	free_list(env_list);
}

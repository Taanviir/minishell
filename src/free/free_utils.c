/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:45:14 by tanas             #+#    #+#             */
/*   Updated: 2023/08/21 16:46:40 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_exec	*exec;
	size_t	i;

	exec = (t_exec *)cmd;
	i = -1;
	while (exec->argv[++i])
		free(exec->argv[i]);
	free(exec->argv);
	free(exec->eargv);
	free(exec);
}

void	free_list(t_env *env_list)
{
	t_env	*temp;
	t_env	*next;

	temp = env_list;
	while (temp)
	{
		next = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		temp = next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:13:46 by tanas             #+#    #+#             */
/*   Updated: 2023/08/17 00:54:12 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*inc_argsize(t_exec *cmd, size_t argc)
{
	t_exec	*ret;

	ret = ft_calloc(sizeof(t_exec), 1);
	ret->argv = ft_calloc(sizeof(char *), (argc + ARGC));
	ret->eargv = ft_calloc(sizeof(char *), (argc + ARGC));
	ft_memcpy(ret, cmd, sizeof(cmd));
	ft_memcpy(ret->argv, cmd->argv, sizeof(char *) * argc);
	ft_memcpy(ret->eargv, cmd->eargv, sizeof(char *) * argc);
	free(cmd->argv);
	free(cmd->eargv);
	free(cmd);
	return (ret);
}

t_cmd	*parseexec(char **b_start, char *b_end, t_env **env_list)
{
	char	*q;
	char	*eq;
	char	*es; // expanded string
	t_exec	*cmd;
	t_cmd	*ret;

	ret = construct_exec();
	cmd = (t_exec *)ret;
	ret = parseredir(ret, b_start, b_end, env_list);
	while (!peek(b_start, b_end, "|&;"))
	{
		if (get_token(b_start, b_end, &q, &eq) != 'a')
			break ;
		es = expand(q, eq, env_list);
		cmd->argv[cmd->argc] = remove_quotes(es, es + ft_strlen(es));
		free(es);
		if ((!cmd->argv[cmd->argc] && (*q - 1) == '"'))
			cmd->argv[cmd->argc] = strdup(" ");
		cmd->eargv[cmd->argc] = cmd->argv[cmd->argc] + ft_strlen(cmd->argv[cmd->argc]);
		if (cmd->argv[cmd->argc])
			cmd->argc++;
		if (cmd->argc > (ARGC - 1))
			cmd = inc_argsize(cmd, cmd->argc);
		ret = parseredir(ret, b_start, b_end, env_list);
	}
	cmd->argv[cmd->argc] = 0;
	cmd->eargv[cmd->argc] = 0;
	return (ret);
}

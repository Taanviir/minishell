/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:13:46 by tanas             #+#    #+#             */
/*   Updated: 2023/08/23 02:57:22 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper function to increase the size of the argument list
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

static char	*__dumb_the_second(char *es, char *q)
{
	if ((!es && (*q - 1) == '"'))
		return (ft_strdup(" "));
	else
		return (remove_quotes(es, es + ft_strlen(es)));
}

/**
 * Parses a buffer to construct and return an executable command object.
 *
 * - Tokenizes the input buffer (`b_start` to `b_end`).
 * - Expands tokens based on the provided environment (`env_list`).
 * - Manages arguments and redirections while populating the executable command.
 *
 * @param b_start Pointer to the start of the buffer to be parsed.
 * @param b_end Pointer to the end of the buffer.
 * @param env_list Reference to the list of environment variables for expansion.
 *
 * @return Returns a pointer to the constructed command object.
 */
t_cmd	*parseexec(char **b_start, char *b_end, t_env **env_list)
{
	char	*q;
	char	*eq;
	char	*es;
	t_exec	*c;
	t_cmd	*ret;

	ret = construct_exec();
	c = (t_exec *)ret;
	ret = parseredir(ret, b_start, b_end, env_list);
	while (!peek(b_start, b_end, "|&;"))
	{
		if (get_token(b_start, b_end, &q, &eq) != 'a')
			break ;
		es = expand(q, eq, env_list, false);
		c->argv[c->argc] = __dumb_the_second(es, q); // ! mallocs here
		free(es);
		c->eargv[c->argc] = c->argv[c->argc] + ft_strlen(c->argv[c->argc]);
		c->argc++;
		if (c->argc > (ARGC - 1))
			c = inc_argsize(c, c->argc);
		ret = parseredir(ret, b_start, b_end, env_list);
	}
	c->argv[c->argc] = 0;
	c->eargv[c->argc] = 0;
	return (ret);
}

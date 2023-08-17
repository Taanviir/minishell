/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:13:46 by tanas             #+#    #+#             */
/*   Updated: 2023/08/17 03:40:29 by sabdelra         ###   ########.fr       */
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

// TODO needs testing
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
	char	*q;		// Start of the current token
	char	*eq;	// End of the current token
	char	*es;	// Expanded token 
	t_exec	*cmd;	// Temporary pointer to assist in command construction.
	t_cmd	*ret;	// Return node

	// initialize the command node
	ret = construct_exec();
	cmd = (t_exec *)ret;
	// Handle redirections if they appear at the start of the buffer
	ret = parseredir(ret, b_start, b_end, env_list);
	// Loop through the buffer until we reach the end or an operator
	while (!peek(b_start, b_end, "|&;"))
	{
		// break out if the token isn't a string
		if (get_token(b_start, b_end, &q, &eq) != 'a')
			break ;
		// expand the token
		es = expand(q, eq, env_list, false);
		// Handle special case for empty double quotes
		if ((!es && (*q - 1) == '"'))
			cmd->argv[cmd->argc] = strdup(" ");
		// remove quotes from the expanded token
		else //! test 
			cmd->argv[cmd->argc] = remove_quotes(es, es + ft_strlen(es));
		free(es); //! test 
		// set the end of the token
		cmd->eargv[cmd->argc] = cmd->argv[cmd->argc] + ft_strlen(cmd->argv[cmd->argc]);
		//! test without the if
		if (cmd->argv[cmd->argc])
			cmd->argc++;
		//! increment the argument count, needs fixing
		if (cmd->argc > (ARGC - 1))
			cmd = inc_argsize(cmd, cmd->argc);
		// parse subsequent redirections
		ret = parseredir(ret, b_start, b_end, env_list);
	}
	// terminate the argument list
	cmd->argv[cmd->argc] = 0;
	cmd->eargv[cmd->argc] = 0;
	return (ret);
}

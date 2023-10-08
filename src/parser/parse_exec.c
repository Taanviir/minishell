/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:13:46 by tanas             #+#    #+#             */
/*   Updated: 2023/10/08 20:48:16 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper function to increase the size of the argument list
static void	inc_argsize(t_exec *cmd, size_t argc_max, size_t argc)
{
	char	**temp_argv;
	char	**temp_eargv;

	temp_argv = cmd->argv;
	temp_eargv = cmd->eargv;
	cmd->argv = ft_calloc(sizeof(char *), (argc_max * 2));
	cmd->eargv = ft_calloc(sizeof(char *), (argc_max * 2));
	ft_memcpy(cmd->argv, temp_argv, sizeof(char *) * argc);
	ft_memcpy(cmd->eargv, temp_eargv, sizeof(char *) * argc);
	cmd->argc_max = argc_max * 2;
	free(temp_argv);
	free(temp_eargv);
}

static char	*open_quotes(char *es, char *q)
{
	if ((!es && (*q - 1) == '"'))
		return (ft_strdup(" "));
	else
		return (remove_quotes(es, es + ft_strlen(es)));
}

t_exec	*fill_execcmd(t_exec *execcmd, char **argq)
{
	execcmd->argv[execcmd->argc] = open_quotes(argq[2], argq[0]);
	free(argq[2]);
	execcmd->eargv[execcmd->argc] = execcmd->argv[execcmd->argc]
		+ ft_strlen(execcmd->argv[execcmd->argc]);
	execcmd->argc++;
	if (execcmd->argc > execcmd->argc_max - 1)
		inc_argsize(execcmd, execcmd->argc_max, execcmd->argc);
	return (execcmd);
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
	char	*argq[3];
	t_exec	*execcmd;
	t_cmd	*ret;
	char	token_type;

	ret = construct_exec();
	execcmd = (t_exec *)ret;
	ret = parseredir(ret, b_start, b_end, env_list);
	while (!peek(b_start, b_end, "|"))
	{
		token_type = get_token(b_start, b_end, &argq[0], &argq[1]);
		if (token_type != 'a')
			break ;
		argq[2] = expand(argq[0], argq[1], env_list, false);
		if (!argq[2])
			continue ;
		execcmd = fill_execcmd(execcmd, argq);
		ret = parseredir(ret, b_start, b_end, env_list);
	}
	execcmd->argv[execcmd->argc] = 0;
	execcmd->eargv[execcmd->argc] = 0;
	if (token_type == 'u')
		return (free_tree(ret), NULL);
	return (ret);
}

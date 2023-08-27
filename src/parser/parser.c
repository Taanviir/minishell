/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:19:12 by eva-1             #+#    #+#             */
/*   Updated: 2023/08/24 17:40:45 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* str is a string of characters to look for
this functions is used to deteremine which parse
function to call */
int	peek(char **b_start, char *b_end, const char *str)
{
	char	*s;

	s = *b_start;
	while (s < b_end && ft_is_whitespace(*s))
		s++;
	*b_start = s;
	return (*s && ft_strchr(str, *s));
}

t_cmd	*parsepipe(char **b_start, char *b_end, t_env **env_list)
{
	t_cmd	*cmd;

	cmd = parseexec(b_start, b_end, env_list);
	if (peek(b_start, b_end, "|"))
	{
		get_token(b_start, b_end, 0, 0);
		if (*b_start == b_end)
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		cmd = construct_pipecmd(cmd, parsepipe(b_start, b_end, env_list));
	}
	return (cmd);
}

t_cmd	*parsecmd(char *b_start, t_env **env_list)
{
	char	*b_end;
	t_cmd	*root;

	if (!b_start[0] || is_empty(b_start))
		return (free(b_start), NULL);
	b_end = ft_strlen(b_start) + b_start;
	root = parsepipe(&b_start, b_end, env_list);
	if (peek(&b_start, b_end, ""))
		ft_putstr_fd("minishell: syntax error\n", 2);
	nullterminate(root);
	return (root);
}

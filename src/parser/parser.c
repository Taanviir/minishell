/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:19:12 by eva-1             #+#    #+#             */
/*   Updated: 2023/08/18 19:03:19 by sabdelra         ###   ########.fr       */
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


//! heredoc if unclosed pipe
t_cmd	*parsepipe(char **b_start, char *b_end, t_env **env_list)
{
	t_cmd	*cmd;

	cmd = parseexec(b_start, b_end, env_list);
	if (peek(b_start, b_end, "|"))
	{
		get_token(b_start, b_end, 0, 0);
		if (*b_start == b_end)
			write(2, "syntax error near unexpected token `|'\n", 39);
		cmd = construct_pipecmd(cmd, parsepipe(b_start, b_end, env_list));
	}
	return (cmd);
}

//! heredoc if unclosed pipe
t_cmd	*parseline(char **b_start, char *b_end, t_env **env_list)
{
	t_cmd	*cmd;

	cmd = parsepipe(b_start, b_end, env_list);
	while (peek(b_start, b_end, "&"))
	{
		get_token(b_start, b_end, 0, 0);
		cmd = construct_bgcmd(cmd);
	}
	while (peek(b_start, b_end, ";"))
	{
		get_token(b_start, b_end, 0, 0);
		if (*b_start == b_end)
			write(2, "syntax error near unexpected token `;'\n", 39);
		cmd = construct_seqcmd(cmd, parseline(b_start, b_end, env_list));
	}
	return (cmd);
}

t_cmd	*nullterminate(t_cmd *cmd)
{
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;
	t_seqcmd	*seqcmd;
	t_bgcmd		*bgcmd;

	if (!cmd)
		return (0);
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		nullterminate(redircmd->cmd);
		if (redircmd->fp) //! here_doc case
			*redircmd->efp = 0;
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		nullterminate(pipecmd->left);
		nullterminate(pipecmd->right);
	}
	else if (cmd->type == SEQUENCE)
	{
		seqcmd = (t_seqcmd *)cmd;
		nullterminate(seqcmd->left);
		nullterminate(seqcmd->right);
	}
	else if (cmd->type == BG)
	{
		bgcmd = (t_bgcmd *)cmd;
		nullterminate(bgcmd->cmd);
	}
	return (cmd);
}

bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

//! fix to adjust for exit, for now it only prints "SYNTAX MF" */
t_cmd	*parsecmd(char *b_start, t_env **env_list)
{
	char	*b_end;
	t_cmd	*root;

	if (!b_start[0] || is_empty(b_start))
		return (free(b_start), NULL);
	b_end = ft_strlen(b_start) + b_start;
	root = parseline(&b_start, b_end, env_list);
	if (peek(&b_start, b_end, ""))
		write(2, "SYNTAX MF\n", 11);
	nullterminate(root);
	return (root);
}

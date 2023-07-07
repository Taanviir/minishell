/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:08:26 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/03 03:06:08by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parseexec(char **b_start, char *b_end);

/* str is a string of characters to look for
this functions is used to deteremine which parse
function to call */
int peek(char **b_start, char *b_end, const char *str)
{
	char	*s;

	s = *b_start;
	while (s < b_end && is_ws(*s))
		s++;
	*b_start = s;
	return (*s && ft_strchr(str, *s));
}

//! error here exit properly */
t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end)
{
	int		redirection;
	char	*q;
	char	*eq;

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (get_token(b_start, b_end, &q, &eq) != 'a')
			write(2, "no file", 8);
		else if (redirection == '<')
			cmd = construct_redircmd(cmd, q, eq, O_RDONLY, STDIN_FILENO);
		else if (redirection == '>')
			cmd = construct_redircmd(cmd, q, eq, O_WRONLY|O_CREAT, STDOUT_FILENO);
		else if (redirection == '+')
			cmd = construct_redircmd(cmd, q, eq, O_WRONLY|O_CREAT|O_APPEND, STDOUT_FILENO);
	}
	return (cmd);
}

t_cmd	*parsepipe(char **b_start, char *b_end)
{
	t_cmd	*cmd;

	cmd = parseexec(b_start, b_end);
	if (peek(b_start, b_end, "|"))
	{
		get_token(b_start, b_end, 0, 0);
		cmd = construct_pipecmd(cmd, parsepipe(b_start, b_end));
	}
	return cmd;
}

t_cmd	*parseline(char **b_start, char *b_end)
{
	t_cmd	*cmd;

	cmd = parsepipe(b_start, b_end);
	while (peek(b_start, b_end, "&"))
	{
		get_token(b_start, b_end, 0, 0);
		cmd = construct_bgcmd(cmd);
	}
	if (peek(b_start, b_end, ";"))
	{
		get_token(b_start, b_end, 0, 0);
		cmd = construct_seqcmd(cmd, parseline(b_start, b_end));
	}
	return (cmd);
}

static t_exec	*inc_argsize(t_exec *cmd, size_t argc)
{
	t_exec		*ret;

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

t_cmd	*parseexec(char **b_start, char *b_end)
{
	char		*q;
	char		*eq;
	int			token;
	size_t		argc;
	t_exec		*cmd;
	t_cmd		*ret;

	argc = 0;
	ret = construct_exec();
	cmd = (t_exec *)ret;
	ret = parseredir(ret, b_start, b_end);
	while (!peek(b_start, b_end, "|&;"))
	{
		if (!(token=get_token(b_start, b_end, &q, &eq)))
			break ;
		if (token != 'a')
			write(2, "sytnax", 7);
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc > (ARGC - 1))
			cmd = inc_argsize(cmd, argc);
		ret = parseredir(ret, b_start, b_end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return ret;
}

t_cmd	*nullterminate(t_cmd *cmd)
{
	t_exec		*execmd;
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;
	t_seqcmd	*seqcmd;
	t_bgcmd		*bgcmd;
	int			i;

	if (!cmd)
		return (0);
	if (!(i = 0) && cmd->type == EXEC)
	{
		execmd = (t_exec *)cmd;
		while (execmd->argv[i])
		{
			*execmd->eargv[i] = 0;
			i++;
		}
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		nullterminate(redircmd->cmd);
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

//! fix to adjust for exit, for now it only prints "SYNTAX MF" */
t_cmd	*parsecmd(char *b_start)
{
	char	*b_end;
	t_cmd	*root;

	b_end = ft_strlen(b_start) + b_start;
	root = parseline(&b_start, b_end);
	if (peek(&b_start, b_end, ""))
		write(2, "SYNTAX MF", 10);
	nullterminate(root);
	return (root);
}


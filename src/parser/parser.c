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

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define SEQUENCE 4
# define BG 5

t_cmd	*parseexec(char **b_start, char *b_end);
/* Constructors */
//! all constructors malloc */
t_cmd	*construct_exec(void)
{
	t_exec	*cmd;

	cmd = ft_calloc(sizeof(t_exec), 1);
	cmd->argv = ft_calloc(sizeof(char *), ARGC);
	cmd->eargv = ft_calloc(sizeof(char *), ARGC);
	cmd->type = EXEC;
	return ((t_cmd *)cmd); // some voodoo shit going on right here
}

t_cmd	*construct_redircmd(t_cmd *command, char *fp, char *efp, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = ft_calloc(sizeof(t_redircmd), 1);
	cmd->type = REDIR;
	cmd->cmd = command;
	cmd->fp = fp;
	cmd->efp = efp;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(sizeof(t_pipecmd), 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*construct_seqcmd(t_cmd *left, t_cmd *right)
{
	t_seqcmd	*cmd;

	cmd = ft_calloc(sizeof(t_seqcmd), 1);
	cmd->type = SEQUENCE;
	cmd->left = left;
	cmd->right = right;
	return((t_cmd *)cmd);
}

t_cmd	*construct_bgcmd(t_cmd *cmd)
{
	t_bgcmd	*bgcmd;

	bgcmd = ft_calloc(sizeof(t_bgcmd), 1);
	bgcmd->type = BG;
	bgcmd->cmd = cmd;
	return((t_cmd *)bgcmd);
}
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
		get_token(b_start, b_end, 0, 0); //! maybe not a good idea to pass null
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
//! fix to adjust for exit, for now it only prints "SYNTAX MF" */
t_cmd	*parsecmd(char *b_start)
{
	char	*b_end;
	t_cmd	*root;

	b_end = ft_strlen(b_start) + b_start;
	root = parseline(&b_start, b_end);
	if (peek(&b_start, b_end, "")) //! testing to see if b_start is now at null
		write(2, "SYNTAX MF", 10);
	/* NULL Terminate?? */
	return (root);
}


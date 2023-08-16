/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:19:12 by eva-1             #+#    #+#             */
/*   Updated: 2023/08/17 00:34:46 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! all these functions need to be static only parsecmd
t_cmd	*parseexec(char **b_start, char *b_end, t_env **env_list);

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

//! error here exit properly */
t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list)
{
	int		redirection;
	int		hc_pipe[2];
	char	*q;
	char	*eq;

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (redirection == '-')
		{
			if (!pipe(hc_pipe))
			{
				cmd = construct_redircmd(cmd, 0, (char *)&hc_pipe[0], O_RDONLY, STDIN_FILENO);
				get_token(b_start, b_end, &q, &eq);
				here_doc(hc_pipe[1], get_delimiter(q, eq), env_list);
				close(hc_pipe[1]); // don't close read end, still needed during execution
			}
			else //TODO pipe error
				perror(":");
		}
		// checking for syntax error in case next token is not a file name, however bash error message takes
		// the last token as the error token, so this is not perfect, this takes the token immediately after
		// redirection
		else if (get_token(b_start, b_end, &q, &eq) != 'a')
		{
			if (eq - q)
			{
				write(2, "minishell: syntax error near unexpected token `", 48);
				write(2, q, eq - q);
				write(2, "\'\n", 2);
			}
			else
				write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
			g_exit_status = 258;
			return (0);
		}
		else if (redirection == '<')
			cmd = construct_redircmd(cmd, q, eq, O_RDONLY, STDIN_FILENO);
		else if (redirection == '>')
			cmd = construct_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (redirection == '+')
			cmd = construct_redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
	}
	return (cmd);
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
	// t_exec		*execmd;
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;
	t_seqcmd	*seqcmd;
	t_bgcmd		*bgcmd;
	int			i;

	if (!cmd)
		return (0);
	i = -1;
	// if (cmd->type == EXEC)
	// {
	// 	execmd = (t_exec *)cmd;
	// 	while (execmd->argv[++i])
	// 		*execmd->eargv[i] = 0; //! segfault
	// }
	// else if (cmd->type == REDIR) //! replace this line with below
	if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		// nullterminate(redircmd->cmd);
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

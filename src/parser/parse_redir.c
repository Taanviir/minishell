/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:41:32 by tanas             #+#    #+#             */
/*   Updated: 2023/10/04 14:28:32 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * checking for syntax error in case next token is not a file name,
 * however bash error message takes the last token as the error token,
 * so this is not perfect, this takes the token immediately after redirection
*/
static t_cmd	*token_error(char *q, char *eq)
{
	if (eq - q)
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		write(2, q, eq - q);
		write(2, "\'\n", 2);
	}
	else
		print_error("syntax error near unexpected token `newline'", NULL);
	g_exit_status = 258;
	return (NULL);
}

static int	*set_open(int mode, int fd, int permissions)
{
	int	*open_conditions;

	open_conditions = malloc(sizeof(int) * 3);
	open_conditions[MODE] = mode;
	open_conditions[FD] = fd;
	open_conditions[PERMISSIONS] = permissions;
	return (open_conditions);
}

static char	*expand_filename(char *q, char *eq, t_env **env_list)
{
	char	*exp_fn;
	char	*end_fn;
	char	*tmp_filename;

	tmp_filename = expand(q, eq, env_list, false);
	end_fn = tmp_filename + ft_strlen(tmp_filename);
	exp_fn = remove_quotes(tmp_filename, end_fn);
	free(tmp_filename);
	return (exp_fn);
}

t_cmd	*commence_redirection(t_cmd *cmd, int redirection, char *full_fn)
{
	if (redirection == '<')
		cmd = (construct_redircmd(cmd, full_fn, set_open(O_RDONLY, 0, 0)));
	else if (redirection == '>')
		cmd = (construct_redircmd(cmd, full_fn, set_open(1537, 1, 436)));
	else if (redirection == '+')
		cmd = (construct_redircmd(cmd, full_fn, set_open(521, 1, 436)));
	return (cmd);
}

t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list)
{
	int		redirection;
	int		pipe_fd[2];
	char	*q;
	char	*eq;
	char	*full_fn;

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (redirection == '-' && verify_pipe(pipe(pipe_fd)))
		{
			cmd = construct_redircmd(cmd, 0, set_open(O_RDONLY, 0, 0));
			((t_redircmd *)cmd)->here_doc = pipe_fd[READ];
			get_token(b_start, b_end, &q, &eq);
			here_doc(pipe_fd[WRITE], get_delimiter(q, eq), env_list);
			close(pipe_fd[WRITE]);
		}
		else if (get_token(b_start, b_end, &q, &eq) == 'a')
			full_fn = expand_filename(q, eq, env_list);
		else
			return (token_error(q, eq));
		cmd = commence_redirection(cmd, redirection, full_fn);
	}
	return (cmd);
}

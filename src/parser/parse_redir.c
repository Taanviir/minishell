/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:41:32 by tanas             #+#    #+#             */
/*   Updated: 2023/09/10 14:35:23 by tanas            ###   ########.fr       */
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

t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list)
{
	int		redirection;
	int		pipe_fd[2];
	char	*q;
	char	*eq;
	char	*expanded_filename;

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (redirection == '-' && verify_pipe(pipe(pipe_fd)))
		{
			cmd = construct_redircmd(cmd, 0, set_open(O_RDONLY, STDIN_FILENO, 0));
			((t_redircmd *)cmd)->here_doc = pipe_fd[READ];
			get_token(b_start, b_end, &q, &eq);
			here_doc(pipe_fd[WRITE], get_delimiter(q, eq), env_list);
			close(pipe_fd[WRITE]);
		}
		else if (get_token(b_start, b_end, &q, &eq) == 'a')
			expanded_filename = expand_filename(q, eq, env_list);
		else
			return (token_error(q, eq));
		if (redirection == '<')
			cmd = construct_redircmd(cmd, expanded_filename, set_open(O_RDONLY, STDIN_FILENO, 0));
		else if (redirection == '>')
			cmd = construct_redircmd(cmd, expanded_filename, set_open(O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
		else if (redirection == '+')
			cmd = construct_redircmd(cmd, expanded_filename, set_open(O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
	return (cmd);
}

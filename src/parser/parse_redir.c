/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:01:49 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/24 21:02:18 by sabdelra         ###   ########.fr       */
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

static int	*so(int mode, int fd)
{
	int		*open_conditions;

	open_conditions = malloc(sizeof(int) * 2);
	open_conditions[MODE] = mode;
	open_conditions[FD] = fd;
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

static t_cmd	*h(int redirection, t_cmd *cmd, char *exp_fn, char *end_fn)
{
	if (redirection == '<')
		return (c_rdr(cmd, exp_fn, end_fn, so(0, 0)));
	else if (redirection == '>')
		return (c_rdr(cmd, exp_fn, end_fn, so(1537, 1)));
	else if (redirection == '+')
		return (c_rdr(cmd, exp_fn, end_fn, so(521, 1)));
	return (NULL);
}

t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list)
{
	int		redirection;
	int		hc_pipe[2];
	char	*argq[2];
	char	*file[2];

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (redirection == '-' && verify_pipe(pipe(hc_pipe)))
		{
			cmd = c_rdr(cmd, 0, (char *)&hc_pipe[0], so(0, 0));
			get_token(b_start, b_end, &argq[0], &argq[1]);
			here_doc(hc_pipe[1], get_delimiter(argq[0], argq[1]), env_list);
			close(hc_pipe[1]);
		}
		else if (get_token(b_start, b_end, &argq[0], &argq[1]) != 'a')
			return (token_error(argq[0], argq[1]));
		else
		{
			file[0] = expand_filename(argq[0], argq[1], env_list);
			file[1] = file[0] + ft_strlen(file[0]);
		}
		cmd = h(redirection, cmd, file[0], file[1]);
	}
	return (cmd);
}

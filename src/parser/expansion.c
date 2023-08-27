/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/24 20:31:56 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Substitutes a given variable (found after a '$' character) with its
 * respective value. The function handles special variables like "$$" for
 * the process ID and "$?" for the exit status. For other variables, it
 * searches the environment array to find the matching key and
 * returns its value.
 *
 * @param q	Pointer to the position in the input string where '$'was found.
 * @param env_array	An array of environment variables in the format "KEY=VALUE".
 *
 * @return	The value of the substituted variable, or NULL if not found.
 * 			The pointer q is also advanced to after the variable name in
 * 			the input string.
 */
static char	*substitute(char **q, char **env_array)
{
	size_t	lvar_s;
	char	*var_s;

	lvar_s = 0;
	var_s = *q + 1;
	if (*var_s == '$')
		return (*q += 2, ft_itoa((int)getpid()));
	else if (*var_s == '?')
		return (*q += 2, ft_itoa(WEXITSTATUS(g_exit_status)));
	else if (ft_is_whitespace(*var_s) || *var_s == '\0' || *var_s == '\"')
		return (*q += 1, ft_strdup("$"));
	*q += 1;
	while (var_s[lvar_s] && ft_is_alnum(var_s[lvar_s]) && var_s[lvar_s] != '_')
	{
		lvar_s++;
		(*q)++;
	}
	while (*env_array)
	{
		if (!ft_strncmp(*env_array, var_s, longer(lvar_s, *env_array)))
			return (ft_strdup(*env_array + lvar_s + 1));
		env_array++;
	}
	return (0);
}

static void	handle_single_quotes(char **q, int *s_quote)
{
	if (!*s_quote && **q == '\'')
		*s_quote = 1;
	else if (*s_quote && **q == '\'')
		*s_quote = 0;
}

static int	handle_double_quotes(char **q, int *d_quote)
{
	if (!*d_quote && **q == '"')
		*d_quote = 1;
	else if (*d_quote && **q == '"')
		*d_quote = 0;
	return (1);
}

static void	expand_env_var(char **q, char **es, char **env_array)
{
	char	*sub;

	sub = substitute(q, env_array);
	if (sub)
		*es = ft_strjoin_m(*es, sub);
	free(sub);
}

/**
 * Expand environment variables contained within a given token.
 *
 * The function scans the token for `$` characters, indicating
 * potential environment variables. If found, the variables are
 * substituted with their values from the environment list.
 *
 * @param q Pointer to the start of the token.
 * @param eq Pointer to the end of the token.
 * @param env_list Pointer to the list of environment variables.
 * @param here_doc A boolean flag to indicate if the function is being called
 * within a heredoc context.
 *
 * @return Returns a newly allocated string with environment variables expanded.
 */
char	*expand(char *q, char *eq, t_env **env_list, bool here_doc)
{
	char	*es;
	char	buffer[2];
	char	**env_array;
	int		qts[2];

	buffer[1] = 0;
	es = NULL;
	env_array = list_to_array(*env_list);
	qts[D] = 0;
	qts[S] = 0;
	while (q < eq)
	{
		if (handle_double_quotes(&q, &qts[D]) && !qts[D])
			handle_single_quotes(&q, &qts[S]);
		if ((!qts[S] || here_doc) && *q == '$' && !ft_is_whitespace(*(q + 1)))
			expand_env_var(&q, &es, env_array);
		else
		{
			buffer[0] = *q;
			es = ft_strjoin_m(es, buffer);
			q++;
		}
	}
	free_double_ptr((void **) env_array);
	return (es);
}

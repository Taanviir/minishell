/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/22 01:15:15 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Compares the lengths of the provided variable and environment variable.
 * The function returns the length of the longer of the two.
 *
 * @param lvar_s: The length of the provided variable.
 * @param env_var: The environment variable string in the format "KEY=VALUE".
 *
 * @return: The length of the longer of the two strings (either lvar_s or the
 * length before '=' in env_var).
 */
static int	longer(int lvar_s, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	if (i > lvar_s)
		return (i);
	else
		return (lvar_s);
}

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
	while (var_s[lvar_s] && !ft_strchr("\" $|;&", var_s[lvar_s]))
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
	int		s_quote;

	buffer[1] = 0;
	es = NULL;
	env_array = list_to_array(*env_list);
	s_quote = 0;
	while (q < eq)
	{
		handle_single_quotes(&q, &s_quote);
		if ((!s_quote || here_doc) && *q == '$' && !ft_is_whitespace(*(q + 1)))
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

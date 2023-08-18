/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:20:49 by tanas             #+#    #+#             */
/*   Updated: 2023/08/17 21:41:52 by sabdelra         ###   ########.fr       */
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
 * @return: The length of the longer of the two strings (either lvar_s or the length before '=' in env_var).
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
 * Substitutes a given variable (found after a '$' character) with its respective value.
 * The function handles special variables like "$$" for the process ID and "$?" for the exit status.
 * For other variables, it searches the environment array to find the matching key and returns its value.
 *
 * @param q			Pointer to the position in the input string where '$' was found.
 * @param env_array	An array of environment variables in the format "KEY=VALUE".
 *
 * @return	The value of the substituted variable, or NULL if not found.
 *          The pointer q is also advanced to after the variable name in the input string.
 */
static char	*substitute(char **q, char **env_array)
{
	size_t	lvar_s;
	char	*var_s;

	lvar_s = 0;
	var_s = *q + 1;
	// Handle special variables
	if (*var_s == '$')
		return (*q += 2, ft_itoa((int)getpid()));
	else if (*var_s == '?')
		return (*q += 2, ft_itoa(WEXITSTATUS(g_exit_status)));
	else if (ft_is_whitespace(*var_s) || *var_s == '\0' || *var_s == '"')
		return (*q += 1, strdup("$"));
	// Advance the pointer to skip the $ character, if it's not a special variable
	*q += 1;
	// Find the length of the variable name, the variable name could end in either a space or a double quote or a dollar sign or any operator
	while (var_s[lvar_s] && !ft_strchr("\" $|;&", var_s[lvar_s]))
	{
		lvar_s++;
		(*q)++;
	}
	// Search the environment array for the variable
	while (*env_array)
	{
		if (!ft_strncmp(*env_array, var_s, longer(lvar_s, *env_array)))
			return (*env_array + lvar_s + 1);
		env_array++;
	}
	// Return NULL if the variable is not found
	return (0);
}

/**
 * Expand environment variables contained within a given token.
 *
 * The function scans the token for `$` characters, indicating potential environment
 * variables. If found, the variables are substituted with their values from
 * the environment list.
 *
 * @param q Pointer to the start of the token.
 * @param eq Pointer to the end of the token.
 * @param env_list Pointer to the list of environment variables.
 * @param here_doc A boolean flag to indicate if the function is being called within
 *                 a heredoc context.
 *
 * @return Returns a newly allocated string with environment variables expanded.
 */
char	*expand(char *q, char *eq, t_env **env_list, bool here_doc)
{
	char	*es; 		// The final expanded string
	char	buffer[2];	// Temporary buffer for single characters
	char	*sub;		// Temporary buffer for substituted variables
	char	**env_array; // Array of environment variables
	int		s_quote;	// Flag to indicate if the current character is within single quotes

	// Null terminate the buffer, because strjoin_m expects null terminated strings
	buffer[1] = 0;
	es = NULL;
	// convert the environment list to an array
	env_array = list_to_array(*env_list);
	s_quote = 0;
	while (q < eq)
	{
		// Check for the start of a single quote
		if (!s_quote && *q == '\'')
			s_quote = 1;
		// Check for the end of a single quote
		else if (s_quote && *q == '\'')
			s_quote = 0;
		// If not in single quotes, or here_doc is true, expand if needed
		if ((!s_quote || here_doc) && *q == '$' && !ft_is_whitespace(*(q + 1)))
		{
			sub = substitute(&q, env_array);
			if (sub)
				es = ft_strjoin_m(es, sub);
		}
		// if not expanding, simply add the character to the expanded string
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

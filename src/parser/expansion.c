/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:28:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/11 02:35:12by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* helper function for substitue
compares the length of the variable
and env_var and returns the longer one */
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

// TODO change var_s name to variable or string, its what ever is after the $
static char	*substitute(char **q, char **env_array)
{
	int		lvar_s;
	char	*var_s;

	lvar_s = 0;
	var_s = *q + 1;
	if (*var_s == '$')
			return (*q += 2, ft_itoa((int)getpid()));
	if (*var_s == '?')
			return (*q += 2, ft_itoa(g_exit_status));
	*q += 1;
	while (var_s[lvar_s] && !ft_is_whitespace(var_s[lvar_s]) && !ft_strchr("\"\'", var_s[lvar_s]))
	{
		lvar_s++;
		(*q)++;
	}
	while (*env_array)
	{
		if (!ft_strncmp(*env_array, var_s, longer(lvar_s, *env_array)))
			return (*env_array + lvar_s + 1);
		env_array++;
	}
	return (0);
}

/* expands a token if it contains a $ */
char	*expand(char *q, char *eq, t_env **env_list)
{
	char	*expanded_string;
	char	buffer[2];
	char	*sub;
	char	**env_array;

	buffer[1] = 0; // this creates a mini null-terminated word to be used with strjoing
	expanded_string = NULL;
	env_array = list_to_array(*env_list);
	while (q < eq)
	{
		if (*q == '$' && !ft_is_whitespace(*(q + 1)))
		{
			sub = substitute(&q, env_array);
			if (sub)
				expanded_string = ft_strjoin_m(expanded_string, sub);
		}
		else
		{
			buffer[0] = *q;
			expanded_string = ft_strjoin_m(expanded_string, buffer);
			q++;
		}
	}
	free_double_ptr((void **) env_array);
	return (expanded_string);
}

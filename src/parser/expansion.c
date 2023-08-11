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

// TODO this WIP
int	g_exit_status = 35; //!remove

/* helper function for substitue
compares the length of the variable
and envp variable and returns the longer */
static int	longer(int lvar_s, char *envp)
{
	int	i;

	i = 0;
	while (envp[i] != '=')
		i++;
	if (i > lvar_s)
		return (i);
	else
		return (lvar_s);
}

// TODO change var_s name to variable or string, its what ever is after the $
static char	*substitute(char **q, char **envp)
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
	while (*envp)
	{
		if (!ft_strncmp(*envp, var_s, longer(lvar_s, *envp)))
			return (*envp + lvar_s + 1);
		envp++;
	}
	return (0);
}

/* expands a token if it contains a $ */
char	*expand(char *q, char *eq, char **envp)
{
	char	*expanded_string;
	char	buffer[2];
	char	*sub;

	buffer[1] = 0; // this creates a mini null-terminated word to be used with strjoing
	expanded_string = NULL;
	while (q < eq)
	{
		if (*q == '$' && !ft_is_whitespace(*(q + 1)))
		{
			sub = substitute(&q, envp);
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
	return (expanded_string);
}

/* int main(__attribute__((unused))int argc,__attribute__((unused))
char **argv, char **envp)
{
	char *test = argv[1];
	// char *test = "$x m l";
	printf("%s\n", expand(test, envp));
} */

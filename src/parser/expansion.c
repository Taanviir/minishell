/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:28:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/02 07:34:18 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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

//not handling ({[]})
static char	*substitute(char **q, char **envp)
{
	int		lvar_s;
	char	*var_s;

	lvar_s = 0;
	var_s = *q + 1;
	if (*(*q + 1))
	{
		if (*(*q + 1) == '$')
			return (ft_itoa((int)getpid()));
		else if (*(*q + 1) == '?')
			return (ft_itoa((int)g_exit_status));
		(*q)++;
	}
	while (var_s[lvar_s] && !is_ws(var_s[lvar_s]))
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
char	*expand(char *q, char **envp)
{
	char	*expanded_string;
	char	buffer[2];
	char	*sub;

	buffer[1] = 0;
	expanded_string = malloc(1);
	if (!expanded_string)
		return (0);
	while (*q)
	{
		if (*q == '$' && !is_ws(*(q + 1)))
		{
			sub = substitute(&q, envp);
			if (sub)
				expanded_string = ft_strjoin(expanded_string, sub);
		}
		else
		{
			buffer[0] = *q;
			expanded_string = ft_strjoin(expanded_string, buffer);
		}
		q++;
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

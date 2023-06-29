/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:28:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/29 06:59:10 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/* Commit
- changed expand to use strjoin and removed [1024]
- added the $$ case expands to calling process ID
- changed substitute to compare based on the longer string
	- case like $X would get matched wrongly with envp XTERM
		since it only compared the first character of envp
		- added helper function to return the longer of the 2
	- added $$ and $? cases to it
- exit status not yet implemented but needed for $? case
	could be a global
 */

int exit_status = 35; //!remove
/* helper function for substitue
compares the length of the variable
and envp variable and returns the longer */
static int	longer(int lvar_s, char *envp) {
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
		{
			(*q)++;
			return(ft_itoa((int)getpid()));
		}
		else if (*(*q + 1) == '?')
		{
			(*q)++;
			return(ft_itoa((int)exit_status));
		}
	}
	while (var_s[lvar_s] && !is_whitespace(var_s[lvar_s]))
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
		if (*q == '$' && !is_whitespace(*(q + 1)))
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

/* int main(__attribute__((unused))int argc,
__attribute__((unused))char **argv, char **envp)
{
	char *test = "$$$$$$ $USER $ USER $$ $$$USER $X $";
	printf("%s\n", expand(test, envp));
	printf("hello");
}
 */
/* TEST_cases
"$$$$$$ $USER $ USER $$ $$$USER $X $"
*all of envp*
""
"!$ m l"
"b !$ l"
"b m !$"
"$USER m l"
"b $USER l"
"b m $USER"
"$$USER m l"
"b $$USER l"
"b m $$USER"
"$$ USER m l"
"b $$ USER l"
"b m $$ USER"
"$ m l"
"b $ l"
"b m $"
"$$$ m l"
"b $$$ l"
"b m $$$"
 */

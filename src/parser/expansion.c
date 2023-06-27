/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:28:01 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/27 17:17:47 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include <string.h>

// /* only simple case of $VAR */
// // assuming it starts after the $ immediatly, not handling ({[]})
// static char	*substitute(char **q, char **envp)
// {
// 	int		i;
// 	char	*var_s;

// 	i = 0;
// 	var_s = *q + 1;
// 	while (var_s[i] && !is_whitespace(var_s[i]))
// 	{
// 		i++;
// 		(*q)++;
// 	}
// 	while (*envp)
// 	{
// 		if (!ft_strncmp(*envp, var_s, i))
// 			return (*envp + i + 1);
// 		envp++;
// 	}
// 	return (0);
// }

// // fix the case if variable isn't found, expand$ returned 0
// //! expanded_string[i++] = *q; this line is risky increment in assignment
// //! [1024] also risky business
// //! not error checking malloc
// //! headsup this function mallocs
// char	*expand(char *q, char **envp)
// {
// 	char	expanded_string[1024];
// 	char	*sub;
// 	int		sub_l;
// 	int		i;

// 	i = 0;
// 	while (*q)
// 	{
// 		if (*q == '$' && !is_whitespace(*(q + 1)))
// 		{
// 			sub = substitute(&q, envp);
// 			if (sub)
// 			{
// 				sub_l = ft_strlen(sub);
// 				ft_strlcat(expanded_string + i, sub, sub_l + 1);
// 				i += sub_l;
// 			}
// 		}
// 		else
// 			expanded_string[i++] = *q;
// 		q++;
// 	}
// 	expanded_string[i] = '\0';
// 	return (ft_memcpy(malloc(i), expanded_string, i + 1));
// }

// int main(__attribute__((unused))int argc,
// __attribute__((unused))char **argv, char **envp)
// {
// 	// char *test = "hello $USER $ <space> $noexist $  USER";
// 	char *test = "hello $USER USER$";
// 	printf("%s\n", expand(test, envp));
// 	printf("hello");
// }


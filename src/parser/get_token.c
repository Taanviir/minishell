/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 07:38:08 by sabdelra          #+#    #+#             */
/*   Updated: 2023/07/16 22:26:32 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #define ALL
/* define ALL for testing all test cases in input array */

static bool    is_opr(char c)
{
    return (c == '<' || c == '|' || c == '>' || c == '&' || c == ';' ||
            c == '(' || c == ')' || c == '{' || c == '}' || c == '=');
}

static bool	check(char c)
{
	return (!ft_is_whitespace(c) && !is_opr(c));
}

/* returns the type of a token,
helper function for get_token */
static char	find_type(char **scan)
{
	int	in_quote;

	in_quote = 0;
	if (!**scan)
		return (0);
	else if (is_opr(**scan))
	{
		if (!ft_strncmp(*scan, ">>", 2) && ((*scan)++))
			return ('+');
		return (**scan);
	}
	in_quote = (**scan == '\"' || **scan == '\'');
	while (scan[0][1] && (in_quote || check(scan[0][1])))
	{
		*scan += 1;
		if (!(*scan - in_quote))
			return ('a');
	}
	return ('a');
}

/*
* Returns the type of token as a char
	- '<' returns '<'
	- '>>' returns +
	- 'a' anything thats not an operator
* Advances the b_start to point to the next token in the buffer
* Sets the q and eq pointers to point to the begining and end
* 	of the token respectively
? note: buffer is the return of readline
*/
char	get_token(char **buffer_start, char *buffer_end,
				char **token_start, char **token_end)
{
	char	token_type;
	char	*scan;

	scan = *buffer_start;
	while (scan < buffer_end && ft_is_whitespace(*scan))
		scan++;
	if (token_start)
		*token_start = scan;
	token_type = find_type(&scan);
	if (*scan)
		scan++;
	if (token_end)
		*token_end = scan;
	while (scan < buffer_end && ft_is_whitespace(*scan))
		scan++;
	*buffer_start = scan;
	return (token_type);
}

// #ifdef ALL
// int main(int argc, char **argv)
// {
// 	char *b_start;
// 	char *b_end;
// 	char *q;
// 	char *eq;
// 	char ret;

// 	b_start = "echo \"hello world!\"";
// 	b_end = b_start + strlen(b_start);
// 	printf("case : '%s'\n", b_start);
// 	while (*b_start) {
// 		q = b_start;
// 		eq = b_start;
// 		ret = get_token(&b_start, b_end, &q, &eq);
// 		printf("%-30.*s", (int)(eq - q), q);
// 		printf("\ttype : %c\n", ret);
// 	}
// 	printf("-------------------------------------------------------\n");

// }
// #endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:29:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/26 16:48:26 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* define ALL for testing all test cases in input array */
# define ALL

static bool	is_whitespace(char c)
{
	char const	*ws;
	int			i;

	ws = " \t\r\n\v";
	i = 0;
	while (ws[i])
	{
		if (!c || c == ws[i])
			return (true);
		i++;
	}
	return (false);
}

static bool	is_operator(char c)
{
	char const	*opr;
	int			i;

	opr = "<|>&;(){}=$";
	i = 0;
	while (opr[i])
	{
		if (!c)
			return (false);
		else if (c == opr[i])
			return (true);
		i++;
	}
	return (false);
}

/* returns the type of a token, helper function for get_token
! use is_operator to replace the while loop
*/
static char	find_type(char **s)
{
	int	single_q;

	single_q = 0;
	if (!**s)
		return (0);
	else if (is_operator(**s))
	{
		if (**s == '>' && *(*s + 1) && *(*s + 1) == '>')
		{
			*s += 1;
			return ('+');
		}
		else
			return (**s);
	}
	if (**s == '\'')
		single_q = 1;
	while ((*(*s + 1) && single_q) || (!is_whitespace(*(*s + 1)) && !is_operator(*(*s + 1))))
	{
		*s += 1;
		if (**s == '\'')
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
* Sets the q and eq pointers to point to the begining and end of the token respectively
? note: buffer is the return of readline
*/
char	get_token(char **b_start, char *b_end,
				char **q, char **eq)
{
	char	ret;
	char	*s;

	s = *b_start;
	while (s < b_end && is_whitespace(*s))
		s++;
	if (q)
		*q = s;
	ret = find_type(&s);
	if (*s)
		s++;
	if (eq)
		*eq = s;
	while (s < b_end && is_whitespace(*s))
		s++;
	*b_start = s;
	return (ret);
}

#ifdef ALL

int main(void)
{
	char *b_start;
	char *b_end;
	char *q;
	char *eq;
	char ret;

	for (int i = 0; INPUT_TEST[i]; i++) {
		b_start = INPUT_TEST[i];
		b_end = b_start + strlen(b_start);
		printf("case : '%s'\n", b_start);
		while (*b_start) {
			q = b_start;
			eq = b_start;
			ret = get_token(&b_start, b_end, &q, &eq);
			printf("%-30.*s", (int)(eq - q), q);
			printf("\t\t\ttype : %c\n", ret);
		}
		printf("---------------------------------------------\n");
	}
}
#endif

#ifdef CASE
int main(int argc, char **argv)
{
	char *b_start;
	char *b_end;
	char *q;
	char *eq;
	char ret;

	b_start = "grep pattern < input.txt > output.txt";
	b_end = b_start + strlen(b_start);
	printf("case : '%s'\n", b_start);
	while (*b_start) {
		q = b_start;
		eq = b_start;
		ret = get_token(&b_start, b_end, &q, &eq);
		printf("%-30.*s", (int)(eq - q), q);
		printf("\ttype : %c\n", ret);
	}
	printf("-------------------------------------------------------\n");

}
#endif



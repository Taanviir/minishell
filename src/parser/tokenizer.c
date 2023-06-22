/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:29:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/22 14:47:18 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* define TEST_ALL for testing all test cases in input array */
#define TEST_ALL

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

static char	is_operator(char c)
{
	char const	*opr;
	int			i;

	opr = "<|>&;(){}=$";
	i = 0;
	while (opr[i])
	{
		if (!c)
			return (0);
		else if (c == opr[i])
			return (opr[i]);
		i++;
	}
	return (0);
}

/* returns the type of a token, helper function for get_token
! use is_operator to replace the while loop
*/
static char	find_type(char **s)
{
	char const	*opr;
	int			i;

	opr = "<|>&;(){}=$";
	i = 0;
	if (is_operator(**s))
	{

	}
	while (opr[i])
	{
		if (!**s)
			return (0);
		else if (**s == '>' && *(*s + 1) && *(*s + 1) == '>')
		{
			*s += 2;
			return ('+');
		}
		else if (**s == opr[i])
		{
			*s += 1;
			return (opr[i]);
		}
		i++;
	}
	if (**s)
		*s += 1;
	while (!is_whitespace(**s) && !is_operator(**s))
		*s += 1;
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
	ret = *s;
	ret = find_type(&s);
	if (eq)
		*eq = s;
	while (s < b_end && is_whitespace(*s))
		s++;
	*b_start = s;
	return (ret);
}

/* #ifdef TEST_ALL
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
			for (char *i = q; i != eq; i++)
				write(1, i, 1);
			printf("\ttype : %c\n", ret);
		}
		printf("---------------------------------------------\n");
	}
}
#endif

#ifdef CASE_I
int main(int argc, char **argv)
{
	char *test = "grep \"pattern\" file.txt";
	t_token *head = tkn_queue(test);
}
#endif */


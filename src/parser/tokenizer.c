/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:29:11 by sabdelra          #+#    #+#             */
/*   Updated: 2023/06/21 17:28:11 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* define TEST_ALL if you want to test all*/
# define TEST_ALL
/* checks if its a white space character from the whitespace string defined above */
static bool is_whitespace(char c)
{
	int	i;
	char const whitespace[6] = " \t\r\n\v";

	i = 0;
	while (whitespace[i]) {
		if (!c || c == whitespace[i])
			return (true);
		i++;
	}
	return (false);
}

char static is_operator(char c)
{
	int	i;
	char const	operators[8] = "<|>&;()";

	i = 0;
	while (operators[i])
	{
		if (!c)
			return (0);
		else if (c == operators[i])
			return operators[i];
		i++;
	}
}

/* checks if a char is an operator if its returns the operator
c has to be a pointer because it needs to move to check for >>
'+' for >>
'a' for anything thats not an operator
*/
static char find_type(char **s)
{
	int			i;
	char const	operators[8] = "<|>&;()";

	i = 0;
	while (operators[i])
	{
		if (!**s)
			return (0); // no token already at end break out.
		else if (**s == '>' && **(s + 1) == '>')
		{
			*s += 2;
			return ('+'); // if >> return +
		}
		else if (**s == operators[i])
		{
			*s += 1;
			return (operators[i]); // if its any other operator
		}
		i++;
	}
	*s += 1;
	while (!is_whitespace(**s) && !is_operator(**s))
		*s += 1;
	return ('a');
}


/*
- Returns the type of token as a char
	- '<' returns '<'
	-'>>' returns +
	- 'a' anything thats not an operator
- Advances the buffer_start to point to the next token in the buffer, and
- Sets the q and eq pointers to point to the begining and end of the token respectively
note: buffer is the return of readline
*/
char get_token(char **buffer_start, char *buffer_end, char **q, char **eq)
{
	char	ret;
	char	*s;

	s = *buffer_start; /* storing the original start of the string */
	while (s < buffer_end && is_whitespace(*s)) // skipping white spaces
		s++;
	if (q)
		*q = s; // if q is not null, need to update it
	ret = *s; // if already at the token set it
	ret = find_type(&s);
	if (eq)
		*eq = s;
	while (s < buffer_end && is_whitespace(*s)) // skipping white spaces
		s++;
	*buffer_start = s;
	return (ret);
}



#ifdef TEST_ALL
int main(int argc, char **argv)
{
	char *buffer_start;
	char *buffer_end;
	char *q;
	char *eq;
	char ret;

	printf("----------------------------------------------------------------------------------------\n\n");
	for (int i = 0; INPUT_TEST[i] && i < 2; i++) {
		buffer_start = INPUT_TEST[i];
		// while (buffer_start) {
			// buffer_end = buffer_start + strlen(buffer_start); buffer end should be this
			printf("------------------TOKEN----------------------\n");
			buffer_end = NULL;
			q = buffer_start;
			eq = buffer_start;
			printf("beg of buf is: '%s'\n", buffer_start);
			printf("get_token\n");
			ret = get_token(&buffer_start, buffer_end, &q, &eq);
			for (char *i = q; i != eq; i++)
				write(1, i, 1);
			write(1, "\n", 1);
			printf("type : %c\n", ret);
			printf("beg of buf is: '%s'\nbeg of token is: '%c'\nend of token is: '%c'\n", buffer_start, *q, *eq);
		// }
		printf("----------------------------------------------------------------------------------------\n\n");
	}
}
#endif

#ifdef CASE_11
int main(int argc, char **argv)
{
	char *test = "grep \"pattern\" file.txt";
	t_token *head = tkn_queue(test);
}
#endif


// TODO case 30 "echo 'Hello' >> file.txt 2>&1" last token??
// TODO maybe quotes are supposed to be part of the token or no? depends on how it will be passed on to execve


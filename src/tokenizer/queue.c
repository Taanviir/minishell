// #include "../../include/cmdtable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct s_token
{
    char *t; // mallocd needs to be freed aswell
    struct s_token *next;
} t_token;


t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->t = token;
	new->next = NULL;
	return (new);
}

/* queue that is based on splitting up the user input into
tokens delimited by space or surrounded by "" or '' */
/* returns the head of a token queue the queue head is returned */
t_token *queue(char *input)
{
	t_token *first = NULL;
	t_token *prev = NULL;
	size_t i;

	i = 0; 
	while (input[i])
	{

		// count the size until the next delimeter
		// delimeter can either be a \0 '"' '\'' or ' '
		char del = '\0'; // starts off as null

		size_t start = i;
		printf("i=%ld\n", i);
		while (input[i] && input[i] != del)
		{
			if (!del && input[i] == '"')
				del = '"';
			else if (!del && input[i] == '\'')
				del = '\'';
			else
				del = ' ';
			i++;
		}
		size_t	token_length = i - start;
		char *token = malloc(sizeof(char) * (token_length + 1));
		if (token)
		{
			strncpy(token, input + start, token_length);
			token[token_length] = '\0';
		}
		t_token *new = create_token(token);
		if (prev) // this is the 2nd new onwards
			prev->next = new;
		if (!first)
			first = new; // new must be first one hmmmm!
		else
			prev = new;
	}
	return (first);
}

int main(int argc, char **argv)
{
	(void)argc;
	t_token *q;

	q = queue(argv[1]);
	for (t_token *temp = q; temp; temp = temp->next)
	{
		printf("%s\n", temp->t);
		printf("%d\n", 3);

	}
}
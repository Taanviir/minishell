#include "../../include/interpreter.h"
// #include "../../include/utils.h"
#include "../../include/interpreter/type.h"
#include <string.h>
/*
Bash Grammar is written in a format called "Backus-Naur Form"
cmd [arg]* [|cmd [arg]* ]* [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
This is an example of shell grammar in Backus-Naur form
*/


/* define TEST_ALL if you want to test all*/

/* Create a t_token, an entry into token linked list */
static t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->token = token;
	new->next = NULL;
	return (new);
}

/* Creates a string from the input, by finding the next token in the input */
static char	*next_token_string(char *input, size_t *i)
{
		char	*token;
		char	del;
		size_t	token_length;

		del = '\0';

		size_t start = *i;
		while (input[*i] && input[*i] != del)
		{
			if (!del && (input[*i] == '"' || input[*i] == '\''))
			{
				del = input[*i];
				start += 1; // to skip the delimiter
			}
			else if (!del || input[*i] == del)
				del = ' ';
			(*i)++;
		}
		token_length = *i - start;
		token = malloc(sizeof(char) * (token_length + 1));
		if (token)
		{
			strncpy(token, input + start, token_length);
			token[token_length] = '\0';
			return (token);
		}
		else
			return (NULL);
}

/* based on matching a pattern set the type field in t_simple_command
pattern is simple either an operator from a list, or no its a word */
/* splits up an input line into tokens with type enum{OPR,WRD} */
/* //!type not implemented yet */

enum TKN_QUEUE {
	first,
	prev,
	temp
};

t_token *tkn_queue(char *input)
{

	t_token	*q[3]; /* position in que (first, prev, temp) */
	size_t	i;

	i = 0;
	while (input[i])
	{
		q[temp] = create_token(next_token_string(input, &i));
		/* adding q[new] token to queue FIFO */
		if (q[prev]) // this is the 2nd new onwards
			q[prev]->next = q[temp];
		if (!q[first])
		{
			q[first] = q[temp]; // new must be first one hmmmm!
			q[prev]= q[first];
		}
		else
			q[prev]= q[temp];
		if (input[i])
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
		}
	}
	q[temp]->next = NULL; // terminating the queue
	return (q[first]); /* head of queue */
}

#ifdef TEST_ALL
int main(int argc, char **argv)
{
	int i = 0;
	for (char *test_case = INPUT_TEST[i]; test_case; i++, test_case = INPUT_TEST[i])
	{
		t_token *token_queue_ll = tkn_queue(test_case);
		printf("Test case no: %d\n", i + 1);
		printf("(%s)\n", test_case);
		for (t_token *temp = token_queue_ll; temp; temp = temp->next)
			printf("%s\n", temp->token);
		printf("______________________________\n");
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


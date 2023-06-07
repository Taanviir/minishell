#include "../../include/interpreter.h"
#include "../../include/interpreter/type.h"

#include <string.h>

/* define TEST_ALL if you want to test all*/

/* Create a t_token, an entry into token que */
t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->token = token;
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

enum TKN_QUEUE {
	first,
	prev,
	temp
};

/* returns a queue FIFO of tokens */
t_queue *interpreter(char *input)
{

	char	*name_token;
	t_token	*temp_token;
	t_queue	*q;
	size_t	i;

	i = 0;
	q = create_queue();
	while (input[i])
	{
		name_token = next_token_string(input, &i);
		temp_token = create_token(name_token);
		/* adding q[new] token to queue FIFO */
		enqueue(temp_token, q);
		if (input[i])
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
		}
	}
	return (q); /* head of queue */
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


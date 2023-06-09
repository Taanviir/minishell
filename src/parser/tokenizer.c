#include "../../include/tokenizer.h"
#include "../../include/tokenizer/type.h"


/* define TEST_ALL if you want to test all*/

/* Create a t_token, an entry into token que */
t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->token = token;
	return (new);
}

/* finds next token and returns a null terminated string of it */
static char	*next_token_string(char *in_cmd, size_t *i)
{
		char	*token;
		char	del;
		size_t	token_length;
		size_t	start;

		del = '\0';
		start = *i;
		while (in_cmd[*i] && in_cmd[*i] != del)
		{
			if (!del && (in_cmd[*i] == '"' || in_cmd[*i] == '\'' || in_cmd[*i] == '\\'))
			{
				del = in_cmd[*i];
				start += 1; // to skip the delimiter
			}
			else if (!del || in_cmd[*i] == del)
				del = ' ';
			(*i)++;
		}
		token_length = *i - start;
		token = malloc(sizeof(char) * (token_length + 1));
		if (token)
		{
			ft_strlcpy(token, in_cmd + start, token_length);
			return (token);
		}
		else
			return (NULL);
}

/* Break up the input command into tokens, and places them in a FIFO queue
returns the queue (t_queue)*/
t_queue *tokenizer(char *input_command)
{

	char	*token_name;
	t_token	*temp;
	t_queue	*token_queue;
	size_t	i;

	i = 0;
	token_queue = create_queue();
	while (input_command[i])
	{
		token_name = next_token_string(input_command, &i);
		temp = create_token(token_name);
		/* adding temp token to queue FIFO */
		enqueue(temp, token_queue);
		if (input_command[i])
		{
			i++;
			while (input_command[i] && input_command[i] == ' ')
				i++;
		}
	}
	return (token_queue);
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


#include "../../include/tokenizer.h"
#include "../../include/tokenizer/type.h"


/* define TEST_ALL if you want to test all*/

/* DELIMITER_FLAG */
#define INSIDE_QUOTES 0X01 /* 0000 0001 */

/* using bitfields
- oring an OPTION  for exampe INSIDE_QUOTES sets on the flag
	INSIDE_QUOTES | int delimter_flag */
#define SET(delmiter, flag) ((delimter, |= (flag)))

/* finds and returns the next token in an input_command string, takes in the string and index pointer */
char *static_find_token(char *input_command, size_t *i, u_int8_t delimter_flag)
{
	/* follows bash grammar rules for determining the meaning of each character based on a set
	of quoting flags
	f1 - inside quotes
	f2 - inside double quotes
	f3 - inside Dollar braces
	f4 - inside  */
	if (input_command[*i] == '\'')
		SET()
}

/* Create a t_token, an entry into token que */
static t_token *create_token(char *token)
{
	t_token *new = malloc(sizeof(t_token));
	new->token = token;
	return (new);
}

/* Break up the input command into tokens, and places them in a FIFO queue
returns the queue (t_queue)*/
t_queue *tokenizer(char *input_command)
{
	t_queue		*token_queue;
	t_token		*token;
	char		*s_token;
	size_t		i;
	u_int8_t	*delimter_flag;

	token_queue = create_queue();
	i = 0;
	while (input_command[i])
	{
		s_token = find_token(input_command, &i, delimter_flag);
		token = create_token(s_token);
		enqueue(token, token_queue);
	}
	enqueue(NULL, token_queue); /* adding a null node to terminate the queue */
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


// TODO case 30 "echo 'Hello' >> file.txt 2>&1" last token?


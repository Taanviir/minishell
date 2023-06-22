#include "minishell.h"
/* The interpreter passes on a queue (FIFO) linked list to the parser
of type t_token *token; a token can be either a WORD or OPERATOR
 The aim of this function here is to create the data structure struct s_simple_command; and ?? Compund_commands*/

/* define TEST_ALL if you want to test all*/

/* Parses the token queue into a simple command struct */
// t_queue	*parse(char *input)
// {
// 	t_queue	*token_queue;

// 	token_queue = get_token(input);
// 	set_type(token_queue);
// 	/*
// 	- set command name
// 	- set size_of_args
// 	- store in argument array
// 	- set redirections based on operators in the token_queue
// 	- set background flag
// 	- has a pointer to next command
// 	 */
// 	return token_queue;
// }

#ifdef TEST_ALL
int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	int i = 0;
	for (char *test_case = INPUT_TEST[i]; test_case; i++, test_case = INPUT_TEST[i])
	{
		t_queue	*token_queue = parse(test_case);
		t_token	*current_token;

		printf("Test case no: %d\n", i + 1);
		printf("(%s)\n", test_case);
		for (t_node *temp = token_queue->first; temp; temp = temp->next)
		{
			current_token = temp->data;
			printf("%s ", current_token->token);
			printf(" type: %s\n", current_token->identifier == OPR? "OPR":"WORD");
		}
		printf("______________________________\n");
	}
}
#endif

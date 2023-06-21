#include "minishell.h"
/* The interpreter passes on a queue (FIFO) linked list to the parser
of type t_token *token; a token can be either a WORD or OPERATOR
 The aim of this function here is to create the data structure struct s_simple_command; and ?? Compund_commands*/

/* define TEST_ALL if you want to test all*/

/* returns true if the token is an operand, and false if else wise */
static bool	is_operand(char *token)
{
	int		i;
	const char	*array_of_operands[27] = {
	";",      // Command separator
	"&&",     // Logical AND
	"||",     // Logical OR
	"&",      // Run command in background
	"|",      // Pipe output to another command
	"<",      // Input redirection from file
	">",      // Output redirection to file (overwrite)
	">>",     // Output redirection to file (append)
	"<<",     // Here document
	"(",      // Start subshell
	")",      // End subshell
	"*",      // Wildcard (matches zero or more characters)
	"?",      // Wildcard (matches a single character)
	"[",      // Test command or file wildcard matching
	"]",      // Test command or file wildcard matching
	"$",      // Variable substitution
	"`",      // Command substitution
	"\"",     // Double quotes (preserve literal meaning of most characters)
	"'",      // Single quotes (preserve literal meaning of all characters)
	"\\n",    // Newline character
	"\\t",    // Tab character
	"\\r",    // Carriage return character
	"\\\"",   // Literal double quote character
	"\\'",    // Literal single quote character
	"\\$",    // Literal dollar sign character
	"\\\\",   // Literal backslash character
	NULL
	};

	i = 0;
	while (array_of_operands[i])
	{
		if (!ft_strncmp(array_of_operands[i], token, ft_strlen(array_of_operands[i])))
			return (true);
		i++;
	}
	return (false);
}

/* takes a token queue as argument and sets the identifier of all the tokens in the que
to either word or operand */
static void set_type(t_queue *queue)
{
	t_token	*current;
	t_node	*temp;

	temp = queue->first;
	if (temp)
	{
		while (temp)
		{
			current = temp->data;
			if(is_operand(current->token))
				current->identifier = OPR;
			else
				current->identifier = WRD;
			temp = temp->next;
		}
	}
}

/* Parses the token queue into a simple command struct */
t_queue	*parse(char *input)
{
	t_queue	*token_queue;

	token_queue = get_token(input);
	set_type(token_queue);
	/*
	- set command name
	- set size_of_args
	- store in argument array
	- set redirections based on operators in the token_queue
	- set background flag
	- has a pointer to next command
	 */
	return token_queue;
}

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
